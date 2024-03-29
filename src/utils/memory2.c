/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:24:56 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/12 12:48:48 by mariaavolet      ###   ########.fr       */
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
		free(terminal->commands->cmd_path);
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

/// @brief This function deallocates the terminal struct and sets 
/// the terminal struct variables to zero.
/// @param terminal 
void	free_terminal(t_terminal *terminal)
{
	free_redir_args(terminal);
	free_commands(terminal);
	free_env_list(&env_api()->env_head);
	free(terminal->prompt);
	free_array(terminal->prompt_splitted);
	ft_bzero(terminal, sizeof(t_terminal));
}

/// @brief This funtions protects in case of a NULL string
/// is returned.
/// (Build outside the orignal scope because of Norminette requirements).
/// @param terminal 
/// @param expand_var 
void	ft_protection_free(t_terminal *terminal, char *var)
{
	free(var);
	free(terminal->prompt);
	free_terminal(terminal);
	malloc_error();
	exit(EXIT_FAILURE);
}
