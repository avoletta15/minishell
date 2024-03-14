/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:20:06 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/13 20:27:41 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief The provided function is a signal handler
/// designed to handle two Unix signals: SIGINT (interrupt signal)
/// and SIGQUIT (quit signal), so ensures proper handling of interrupt
/// and quit signals, providing appropriate responses 
/// depending on the circumstances.
/// @param signal 
static void	sigint_handler(int signal)
{
	(void)signal;
	get_terminal()->exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/// @brief This sets the parent process to ignore the
/// interrupt and quit signals.
/// @param  
void	handle_parent_execution_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/// @brief This function sets the default signal handler
/// for the parent process.
/// @param  
void	handle_parent_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
