/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:50:20 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/27 14:52:54 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function allocates a new buffer
/// tries to copy the prompt replacing the
/// whitespaces for a special char in valid 
/// places and if something goes wrong it
/// deallocates the memory and returns NULL.
/// @param quote 
/// @return 
char	*first_filter(t_quotes_system *quote)
{
	char	*new_prompt;

	new_prompt = (char *)malloc(sizeof(char) * ft_strlen(quote->prompt) + 1);
	if (!new_prompt)
	{
		free_project(quote, &malloc_error);
		return (NULL);
	}
	remove_whitespaces(new_prompt, quote->prompt, quote);
	if (quote->quote_state)
	{
		free_project(quote, &bad_syntax_error);
		return (NULL);
	}
	free(quote->prompt);
	return (new_prompt);
}

/// @brief This function allocates a new buffer and places before
/// and after each special character, such as redirects and pipes,
/// the separator character, preparing it to the split function.
/// @param quote 
/// @return 
char	*second_filter(t_quotes_system *quote)
{
	char	*new_prompt;

	new_prompt = (char *)malloc(sizeof(char)
			* ft_strlen(quote->prompt) * 2 + 1);
	if (!new_prompt)
	{
		free_project(quote, &malloc_error);
		return (NULL);
	}
	delimit_special_chars(new_prompt, quote->prompt, quote);
	free(quote->prompt);
	return (new_prompt);
}

/// @brief This function tranforms the modified prompt with the
/// special character placed at the correct spots into an array
/// of strings.
/// @param quote 
/// @return 
char	**third_filter(t_quotes_system *quote)
{
	char	**prompt_splitted;

	prompt_splitted = ft_split(quote->prompt, PARSER_SEP);
	if (!prompt_splitted)
	{
		free_project(quote, &malloc_error);
		return (NULL);
	}
	free(quote->prompt);
	return (prompt_splitted);
}

/// @brief This function treats the original prompt and
/// returns true if it was successfull, otherwise false.
/// @param quote 
/// @return 
bool	lexer(t_program *program)
{
	t_quotes_system	*quote;

	quote = &program->quotes_system;
	quote->prompt = first_filter(quote);
	if (!quote->prompt)
		return (false);
	quote->prompt = second_filter(quote);
	if (!quote->prompt)
		return (false);
	quote->prompt_splitted = third_filter(quote);
	if (!quote->prompt_splitted)
		return (false);
	tokenize_prompt(quote->prompt_splitted, &program->tokens);
	if (!program->tokens)
		return (false);
	return (true);
}
