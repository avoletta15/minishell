/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:24:56 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/03 16:23:00 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_terminal *terminal)
{
	t_command	*curr;

	curr = terminal->commands;
	while (curr)
	{
		curr = curr->next;
		free_prompt(terminal->commands->args);
		free_redirect(terminal->commands->redirections);
		free(terminal->commands);
		terminal->commands = curr;
	}
}

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
