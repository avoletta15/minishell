/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:48:19 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/16 15:56:57 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function displays an error message when the
/// redirection is ambiguous. It always returns false.
/// @param redir 
/// @return 
bool	ambiguous_redir_error(char *content)
{
	t_terminal	*terminal;

	terminal = get_terminal();
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(content, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	terminal->exit_status = FAILURE;
	return (false);
}
