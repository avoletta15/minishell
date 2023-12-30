/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:39:58 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/30 17:31:56 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function initializes the terminal's variable.
/// @param terminal 
void	init_program(t_terminal *terminal, bool reset_all)
{
	terminal->prompt = NULL;
	terminal->prompt_splitted = NULL;
	terminal->commands = NULL;
	terminal->tokens = NULL;
	if (reset_all)
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
void	reset_terminal(t_terminal *terminal, bool reset_all)
{
	return (init_program(terminal, reset_all));
}
