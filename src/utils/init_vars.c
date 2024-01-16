/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:39:58 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/02 16:25:44 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function initializes the terminal's variable.
/// @param terminal 
void	init_terminal(t_terminal *terminal, int exit_status)
{
	terminal->prompt = NULL;
	terminal->prompt_splitted = NULL;
	terminal->commands = NULL;
	terminal->tokens = NULL;
	terminal->args = NULL;
	terminal->redirects = NULL;
	terminal->exit_status = exit_status;
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
void	reset_terminal(t_terminal *terminal, int exit_status)
{
	return (init_terminal(terminal, exit_status));
}
