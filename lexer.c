/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:50:20 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/03 16:54:32 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function allocates a new buffer
/// tries to copy the prompt replacing the
/// whitespaces for a special char in valid 
/// places and if something goes wrong it
/// deallocates the memory and returns NULL.
/// @param terminal 
/// @return 
bool	first_filter(t_terminal *terminal)
{
	char	*new_prompt;

	new_prompt = (char *)malloc(sizeof(char) * ft_strlen(terminal->prompt) + 1);
	if (!new_prompt)
	{
		free(terminal->prompt);
		malloc_error();
		exit(EXIT_FAILURE);
	}
	remove_whitespaces(new_prompt, terminal->prompt, &terminal->quotes_system);
	if (terminal->quotes_system.quote_state)
	{
		free(new_prompt);
		unclosed_quote_error();
		reset_terminal(terminal, BAD_SYNTAX);
		return (false);
	}
	free(terminal->prompt);
	terminal->prompt = new_prompt;
	return (true);
}

/// @brief This function allocates a new buffer and places before
/// and after each special character, such as redirects and pipes,
/// the separator character, preparing it to the split function.
/// @param terminal 
/// @return 
bool	second_filter(t_terminal *terminal)
{
	char	*new_prompt;

	new_prompt = (char *)malloc(sizeof(char)
			* ft_strlen(terminal->prompt) * 3 + 1);
	if (!new_prompt)
	{
		free(terminal->prompt);
		malloc_error();
		exit(EXIT_FAILURE);
	}
	delimit_special_chars(new_prompt, terminal->prompt,
		&terminal->quotes_system);
	free(terminal->prompt);
	terminal->prompt = new_prompt;
	return (true);
}

/// @brief This function tranforms the modified prompt with the
/// special character placed at the correct spots into an array
/// of strings.
/// @param terminal
/// @return 
bool	third_filter(t_terminal *terminal)
{
	char	**prompt_splitted;

	prompt_splitted = ft_split(terminal->prompt, PARSER_SEP);
	if (!prompt_splitted)
	{
		free(terminal->prompt);
		malloc_error();
		exit(EXIT_FAILURE);
	}
	free(terminal->prompt);
	terminal->prompt = NULL;
	terminal->prompt_splitted = prompt_splitted;
	return (true);
}

/// @brief This function treats the original prompt and
/// returns true if it was successfull, otherwise false.
/// @param quote 
/// @return 
bool	lexer(t_terminal *terminal)
{
	if (!first_filter(terminal))
		return (false);
	second_filter(terminal);
	third_filter(terminal);
	tokenize_prompt(terminal, &terminal->tokens);
	if (!tokens_checker(terminal))
		return (false);
	return (true);
}
