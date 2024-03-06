/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:24:56 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/05 10:57:38 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function deallocates all commands.
/// @param terminal 
void	free_commands(t_terminal *terminal)
{
	t_command	*curr;

	curr = terminal->commands;
	while (curr)
	{
		curr = curr->next;
		free_array(terminal->commands->args);
		free_redirect(terminal->commands->redirections);
		free(terminal->commands);
		terminal->commands = curr;
	}
}

/// @brief This function deallocates all structs and executes a function
/// if it's different than `NULL`. It exists the program if the second
/// parameter is true, otherwise the exit function will be ignored.
/// @param terminal 
/// @param should_exit 
/// @param call_back 
void	free_structs(t_terminal *terminal,
		bool should_exit, void (*call_back)(void))
{
	free_redir_args(terminal);
	free_commands(terminal);
	if (call_back)
		call_back();
	if (should_exit)
		exit(EXIT_FAILURE);
}
