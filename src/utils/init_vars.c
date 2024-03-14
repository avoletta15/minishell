/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:39:58 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/13 21:22:41 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function initializes the terminal's variable.
/// @param terminal 
void	init_terminal(t_terminal *terminal)
{
	terminal->prompt = NULL;
	terminal->prompt_splitted = NULL;
	terminal->commands = NULL;
	terminal->tokens = NULL;
	terminal->args = NULL;
	terminal->redirects = NULL;
	terminal->exit_status = 0;
	init_quotes_system(&terminal->quotes_system);
}

/// @brief This function initializes the quotes system variables.
/// @param quotes_system 
void	init_quotes_system(t_quotes_system *quotes_system)
{
	quotes_system->quote = 0;
	quotes_system->quote_state = false;
}

/// @brief This function resets the variables
/// from the terminal, such as prompt, prompt_splitted,
/// commands, tokens, and quotes_system.
/// @param terminal 
void	reset_terminal(t_terminal *terminal)
{
	free_redir_args(terminal);
	free_commands(terminal);
	free_env_list(&env_api()->env_head);
	free(terminal->prompt);
	free_array(terminal->prompt_splitted);
	terminal->prompt = NULL;
	terminal->prompt_splitted = NULL;
	terminal->commands = NULL;
	terminal->tokens = NULL;
	terminal->args = NULL;
	terminal->redirects = NULL;
}
