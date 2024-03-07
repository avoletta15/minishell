/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:03:47 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/07 18:25:57 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function writes to the write end of the here_doc pipe.
/// and closes the write end of the pipe. It exits with success.
/// @param fd 
/// @param delimiter 
void	write_to_here_doc_pipe(t_terminal *terminal, int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
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
	free_terminal(terminal);
	exit(EXIT_SUCCESS);
}

/// @brief This function creates a child process and writes to the write end
/// of the here_doc pipe. It closes the read end of the pipe and waits for
/// the child process to finish. On error, it displays an error message
/// and closes the pipe_fd.
/// @param redir 
/// @param in 
/// @param out 
void	here_doc_child(t_terminal *terminal, t_redirect *redir,
		int in, int out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close_fds(in, out);
		return ;
	}
	if (pid == 0)
	{
		close(in);
		write_to_here_doc_pipe(terminal, out, redir->content);
	}
	else
	{
		close(out);
		redir->fd = in;
		waitpid(pid, NULL, 0);
	}
}

/// @brief This function creates a pipe and calls the here_doc_child function.
/// On error, it displays an error message.
/// @param redir 
void	handle_here_doc_pipes(t_terminal *terminal, t_redirect *redir)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		ft_putstr_fd("minishell: pipe: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	here_doc_child(terminal, redir, pipe_fd[0], pipe_fd[1]);
}

/// @brief This function iterates through the redirections and calls the
/// handle_here_doc_pipes function if the redirection is a here_doc.
/// @param redir 
void	check_here_doc(t_terminal *terminal, t_redirect *redir)
{
	while (redir)
	{
		if (redir->toked_id == HERE_DOC_ID)
			handle_here_doc_pipes(terminal, redir);
		redir = redir->next;
	}
}

/// @brief This is the main function of the here_doc module. It iterates
/// through the commands and calls the check_here_doc function if the
/// command has redirections.
/// @param terminal 
void	here_doc(t_terminal *terminal)
{
	t_command	*cmd;

	cmd = terminal->commands;
	while (cmd)
	{
		if (cmd->redirections)
			check_here_doc(terminal, cmd->redirections);
		cmd = cmd->next;
	}
}
