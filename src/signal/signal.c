/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:10 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/12 19:28:54 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/// @brief The provided function is a signal handler designed to handle two Unix 
/// signals: SIGINT (interrupt signal) and SIGQUIT (quit signal), so ensures proper 
/// handling of interrupt and quit signals, providing appropriate responses 
/// depending on the circumstances.
/// @param signal 
static void	sigint_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_parent_execution_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_parent_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	here_doc_sigint(int signal)
{
	(void)signal;
	get_terminal()->hd_exit = true;
	close(STDIN_FILENO);
}

void	handle_heredoc_signals(void)
{
	signal(SIGINT, here_doc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// SIGINT (CTRL+C) -> clear prompt and reset line
//	(disabled while executing (including heredoc), by a variable or setting to sigign and resetting to the handler after the execution)
// SIGQUIT (CTRL+\) -> ignore

// inside childs:
// 	SIGINT (CTRL+C) -> default
// 	SIGQUIT (CTRL+\) -> default

// inside heredoc:
// 	SIGINT (CTRL+C) -> default
// 	SIGQUIT (CTRL+\) -> ignore (use termios to remove the \ char)