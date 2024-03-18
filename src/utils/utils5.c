/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:57:27 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/18 11:51:29 by arabelo-         ###   ########.fr       */
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
void	close_cmds_fds(t_command *cmd, bool close_pipe)
{
	while (cmd)
	{
		if (cmd->redirections)
			close_redirect_fds(cmd->redirections);
		if (close_pipe)
			close_fds(cmd->pipe_fd[0], cmd->pipe_fd[1]);
		close_fds(cmd->std_fds.in, cmd->std_fds.out);
		cmd = cmd->next;
	}
}

/// @brief This function returns the terminal's address.
/// @param  
/// @return 
t_terminal	*get_terminal(void)
{
	static t_terminal	terminal;

	return (&terminal);
}

/// @brief This function checks if the given character is a quote
/// and updates the quotes_system struct, then it increments the
/// iterator if the character is not the null terminator.
/// @param quotes_sys 
/// @param c 
void	quotes_iterator(t_quotes_system *quotes_sys, char c)
{
	if (!c)
		return ;
	if ((c == DOUBLE_QUOTE || c == SINGLE_QUOTE) && !quotes_sys->quote_state)
	{
		quotes_sys->quote_state = true;
		quotes_sys->was_quoted = true;
		quotes_sys->quote = c;
	}
	else if (c == quotes_sys->quote && quotes_sys->quote_state)
	{
		quotes_sys->quote_state = false;
		quotes_sys->quote = 0;
	}
	quotes_sys->i++;
}

/// @brief This function searches for the sub character in the string
/// and replaces it with the to_replace character.
/// @param str 
/// @param sub 
/// @param to_replace 
void	str_chr_subs(char *str, char sub, char to_replace)
{
	while (str && *str)
	{
		if (*str == sub)
			*str = to_replace;
		str++;
	}
}
