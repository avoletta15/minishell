/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:10 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/07 19:03:01 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/// @brief This funtion sets a static variable into the correspondent exit code
/// each time is called usuing the code passed as argument (int code)
/// @param i 
/// @param flag 
/// @return 
int	set_exit_code(int i, bool flag)
{
	static int	code;

	if (flag)
		code = i;
	return (code);
}


/// @brief The provided function is a signal handler designed to handle two Unix 
/// signals: SIGINT (interrupt signal) and SIGQUIT (quit signal), so ensures proper 
/// handling of interrupt and quit signals, providing appropriate responses 
/// depending on the circumstances.
/// @param signal 
void	signal_handler(int signal)
{
	pid_t	pid;
	int		status_ptr;

	pid = waitpid(-1, &status_ptr, 0);
	if (signal == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
	if (signal == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}
