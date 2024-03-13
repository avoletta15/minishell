/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:03:47 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/12 19:30:27 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

/// @brief This function writes to the write end of the here_doc pipe.
/// and closes the write end of the pipe. It exits with success.
/// @param fd 
/// @param delimiter 
static void	write_to_here_doc_pipe(t_terminal *terminal, int fd, char *delimiter)
{
	char	*line;
	bool	sigint;
	struct termios original;
	struct termios term;

	if (tcgetattr(STDOUT_FILENO, &term) == 0)
	{
		original = term;
		term.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	}

	sigint = false;
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			sigint = get_terminal()->hd_exit;
			if (!sigint)
				here_doc_ctrl_d(delimiter);
			break ;
		}
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	close_cmds_fds(terminal->commands, false);
	free_terminal(terminal);
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &original) == -1)
		perror("tcsetattr"); 
	if (sigint)
	{
		write(STDERR_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/// @brief This function creates a child process and writes to the write end
/// of the here_doc pipe. It closes the read end of the pipe and waits for
/// the child process to finish. On error, it displays an error message
/// and closes the pipe_fd.
/// @param redir 
/// @param in 
/// @param out 
static bool	here_doc_child(t_terminal *terminal, t_redirect *redir, int *fds)
{
	pid_t	pid;
	int	status;

	redir->fd = fds[0];
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close_fds(fds[0], fds[1]);
		return (false);
	}
	if (pid == 0)
	{
		handle_heredoc_signals();
		close(fds[0]);
		write_to_here_doc_pipe(terminal, fds[1], redir->content);
	}
	else
	{
		close(fds[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status) == 0);
	}
	return (false);
}

/// @brief This function creates a pipe and calls the here_doc_child function.
/// On error, it displays an error message.
/// @param redir 
static bool	handle_here_doc_pipes(t_terminal *terminal, t_redirect *redir)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		ft_putstr_fd("minishell: pipe: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (false);
	}
	return (here_doc_child(terminal, redir, pipe_fd));
}

/// @brief This function iterates through the redirections and calls the
/// handle_here_doc_pipes function if the redirection is a here_doc.
/// @param redir 
bool	check_here_doc(t_terminal *terminal, t_command *cmd)
{
	t_redirect	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->toked_id == HERE_DOC_ID && !handle_here_doc_pipes(terminal, redir))
			return (false);
		redir = redir->next;
	}
	return (true);
}

/// @brief This is the main function of the here_doc module. It iterates
/// through the commands and calls the check_here_doc function if the
/// command has redirections.
/// @param terminal 
bool	here_doc(t_terminal *terminal)
{
	t_command	*cmd;

	cmd = terminal->commands;
	while (cmd)
	{
		if (cmd->redirections && !check_here_doc(terminal, cmd))
			return (false);
		cmd = cmd->next;
	}
	return (true);
}
