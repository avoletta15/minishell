/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:39:58 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/30 17:12:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function initializes the program's variable.
/// @param program 
void	init_program(t_program *program, bool reset_all)
{
	program->prompt = NULL;
	program->prompt_splitted = NULL;
	program->commands = NULL;
	program->tokens = NULL;
	if (reset_all)
		program->exit_status = 0;
	init_quotes_system(&program->quotes_system);
}

/// @brief This function initializes the quotes system variables.
/// @param quotes_system 
void	init_quotes_system(t_quotes_system *quotes_system)
{
	quotes_system->quote = 0;
	quotes_system->quote_state = false;
}

/// @brief This function resets the variables
/// from the program, such as prompt, prompt_splitted,
/// commands, tokens, and quotes_system.
/// @param program 
void	reset_program(t_program *program, bool reset_all)
{
	return (init_program(program, reset_all));
}
