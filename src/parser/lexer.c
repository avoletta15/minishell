/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:50:20 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/14 18:59:32 by arabelo-         ###   ########.fr       */
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
bool	first_filter(char *str, t_quotes_system *quotes)
{
	subsquote(str, quotes);
	if (quotes->quote_state)
	{
		unclosed_quote_error();
		return (false);
	}
	remove_whitespaces(str, quotes);
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
	add_history(terminal->prompt);
	if (only_white_spaces(terminal->prompt))
		return (false);
	if (!first_filter(terminal->prompt, &terminal->quotes_system))
	{
		reset_terminal(terminal);
		terminal->exit_status = BAD_SYNTAX;
		return (false);
	}
	second_filter(terminal);
	third_filter(terminal);
	tokenize_prompt(terminal, &terminal->tokens);
	if (!tokens_checker(terminal))
	{
		free_tokens(terminal->tokens);
		return (false);
	}
	return (true);
}
