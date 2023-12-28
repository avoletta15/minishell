/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:39:58 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/28 20:36:24 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function initializes the program's variable.
/// @param program 
void	init_program(t_program *program)
{
	program->command_line = NULL;
	program->commands = NULL;
	program->tokens = NULL;
	init_quotes_system(&program->quotes_system);
}

/// @brief This function initializes the quotes system variables.
/// @param quotes_system 
void	init_quotes_system(t_quotes_system *quotes_system)
{
	quotes_system->prompt = NULL;
	quotes_system->prompt_splitted = NULL;
	quotes_system->quote = 0;
	quotes_system->quote_state = false;
}
