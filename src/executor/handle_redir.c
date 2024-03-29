/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:22:32 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/16 15:56:45 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function displays an error message when the
/// open function fails. It always returns false.
/// @param file 
/// @return 
bool	open_error(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (false);
}

/// @brief This function checks which input redirection should be
/// executed and opens the file with the given flags. It changes the value
/// of the pointers new_fd and in to the new file descriptor if the
/// redirection is a regular input, else changes only the value of the
/// in pointer, closing the old input file descriptor if it is different
/// from the standard input.
/// @param redir 
/// @param in 
/// @param new_fd 
void	handle_input_files(t_redirect *redir, int *in, int *new_fd)
{
	if (redir->toked_id == INPUT_REDIRECT_ID)
	{
		*new_fd = open(redir->content, O_RDONLY);
		close_fds(*in, STDOUT_FILENO);
		*in = *new_fd;
	}
	else
	{
		close_fds(*in, STDOUT_FILENO);
		*in = redir->fd;
	}
}

/// @brief This function checks which output redirection should be
/// executed and opens the file with the given flags. It changes the value
/// of the pointers new_fd and out to the new file descriptor, closing the
/// old output file descriptor if it is different from the standard output.
/// @param redir 
/// @param out 
/// @param new_fd 
void	handle_output_files(t_redirect *redir, int *out, int *new_fd)
{
	if (redir->toked_id == APPEND_ID)
	{
		*new_fd = open(redir->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		close_fds(STDIN_FILENO, *out);
		*out = *new_fd;
	}
	else
	{
		*new_fd = open(redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close_fds(STDIN_FILENO, *out);
		*out = *new_fd;
	}
}

/// @brief This function checks which redirection should be executed and
/// opens the file with the given flags. It changes the value of the pointers
/// in and out to the new file descriptor.
/// @param redir 
/// @param in 
/// @param out 
/// @return 
int	handle_open(t_redirect *redir, int *in, int *out)
{
	int	new_fd;

	new_fd = 0;
	if (redir->invalid_expansion)
		return (-2);
	if (redir->toked_id == APPEND_ID || redir->toked_id == OUTPUT_REDIRECT_ID)
		handle_output_files(redir, out, &new_fd);
	else
		handle_input_files(redir, in, &new_fd);
	return (new_fd);
}

/// @brief This function handles the redirections of the command.
/// It changes the file descriptors of the input and output to the
/// new file descriptors of the redirections.
/// @param cmd 
/// @param in 
/// @param out
/// @return 
bool	redirection_handle(t_command *cmd, bool parent)
{
	t_redirect	*redir;
	int			new_fd;

	redir = cmd->redirections;
	while (redir)
	{
		new_fd = handle_open(redir, &cmd->std_fds.in, &cmd->std_fds.out);
		if (new_fd == -1)
			return (open_error(redir->content));
		else if (new_fd == -2)
			return (ambiguous_redir_error(redir->content));
		redir = redir->next;
	}
	if (!parent)
	{
		dup2(cmd->std_fds.in, STDIN_FILENO);
		dup2(cmd->std_fds.out, STDOUT_FILENO);
	}
	if (cmd->std_fds.in == -1)
		cmd->std_fds.in = STDIN_FILENO;
	if (cmd->std_fds.out == -1)
		cmd->std_fds.out = STDOUT_FILENO;
	return (true);
}
