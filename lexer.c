/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:50:20 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/29 19:26:21 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function allocates a new buffer
/// tries to copy the prompt replacing the
/// whitespaces for a special char in valid 
/// places and if something goes wrong it
/// deallocates the memory and returns NULL.
/// @param program 
/// @return 
bool	first_filter(t_program *program)
{
	char	*new_prompt;

	new_prompt = (char *)malloc(sizeof(char) * ft_strlen(program->prompt) + 1);
	if (!new_prompt)
	{
		free_project(program, &malloc_error);
		exit(EXIT_FAILURE);
	}
	remove_whitespaces(new_prompt, program->prompt, &program->quotes_system);
	if (program->quotes_system.quote_state)
	{
		free_project(program, &unclosed_quote_error);
		return (false);
	}
	free(program->prompt);
	program->prompt = new_prompt;
	return (true);
}

/// @brief This function allocates a new buffer and places before
/// and after each special character, such as redirects and pipes,
/// the separator character, preparing it to the split function.
/// @param program 
/// @return 
bool	second_filter(t_program *program)
{
	char	*new_prompt;

	new_prompt = (char *)malloc(sizeof(char)
			* ft_strlen(program->prompt) * 3 + 1);
	if (!new_prompt)
	{
		free_project(program, &malloc_error);
		exit(EXIT_FAILURE);
	}
	delimit_special_chars(new_prompt, program->prompt, &program->quotes_system);
	free(program->prompt);
	program->prompt = new_prompt;
	return (true);
}

/// @brief This function tranforms the modified prompt with the
/// special character placed at the correct spots into an array
/// of strings.
/// @param program
/// @return 
bool	third_filter(t_program *program)
{
	char	**prompt_splitted;

	prompt_splitted = ft_split(program->prompt, PARSER_SEP);
	if (!prompt_splitted)
	{
		free_project(program, &malloc_error);
		exit(EXIT_FAILURE);
	}
	free(program->prompt);
	program->prompt = NULL;
	program->prompt_splitted = prompt_splitted;
	return (true);
}

/// @brief This function treats the original prompt and
/// returns true if it was successfull, otherwise false.
/// @param quote 
/// @return 
bool	lexer(t_program *program)
{
	if (!first_filter(program))
		return (false);
	second_filter(program);
	third_filter(program);
	tokenize_prompt(program, &program->tokens);
	if (!tokens_checker(program))
		return (false);
	return (true);
}
