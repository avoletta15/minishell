/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:10 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/18 11:51:02 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function sets the default signal handler for the child process.
/// @param  
void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/// @brief This function sets the signal handler for the here_doc process.
/// sets the exit status to 130, the here doc exit flag to true
/// and closes the standard input.
/// @param signal 
static void	here_doc_sigint(int signal)
{
	(void)signal;
	get_terminal()->hd_exit = true;
	get_terminal()->exit_status = 130;
	close(STDIN_FILENO);
}

/// @brief This function sets the signal handler for the here_doc process.
/// @param  
void	handle_heredoc_signals(void)
{
	signal(SIGINT, here_doc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
