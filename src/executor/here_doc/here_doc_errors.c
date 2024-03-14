/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:02 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/13 21:39:28 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function displays an warning message when the here_doc
/// is cancelled by the user unsing control + D.
/// @param delimiter 
void	here_doc_ctrl_d(char *delimiter)
{
	write(STDOUT_FILENO,
		"here-document delimited by end-of-file (wanted `", 48);
	write(STDOUT_FILENO, delimiter, ft_strlen(delimiter));
	write(STDOUT_FILENO, "')\n", 3);
}

/// @brief This function displays an error message when the here_doc
/// fork fails and closes the pipe_fd.
/// @param fds 
void	here_doc_fork_error(int *fds)
{
	ft_putstr_fd("minishell: fork: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	close_fds(fds[0], fds[1]);
}
