/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:57:27 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/07 17:58:50 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This funciton closes the file descriptors if they are not -1
/// of all the redirections in the given list.
/// @param redir 
void	close_redirect_fds(t_redirect *redir)
{
	while (redir)
	{
		if (redir->fd != -1)
			close(redir->fd);
		redir = redir->next;
	}
}

/// @brief This function calls the close_redirect_fds function and
/// closes the file descriptors if they are not -1 or STDIN_FD STDOUT_FD 
/// of all the commands.
/// @param cmd 
void	close_cmds_fds(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->redirections)
			close_redirect_fds(cmd->redirections);
		close_fds(cmd->std_fds.in, cmd->std_fds.out);
		close_fds(cmd->pipe_fd[0], cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
}
