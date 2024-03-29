/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_treatment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:21:05 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/14 18:58:27 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function places the separator character before
/// and after the special characters, such as redirects and pipes,
/// only outside quotes.
/// @param dest 
/// @param src 
/// @param quote 
void	delimit_special_chars(char *dest,
		char *src, t_quotes_system *quote)
{
	int		pos;

	while (src && *src)
	{
		pos = is_special_chars(src);
		if (pos != -1 && !quote->quote_state)
			put_separator(&dest, &src, &pos);
		else if (!quote->quote_state
			&& (*src == SINGLE_QUOTE || *src == DOUBLE_QUOTE))
		{
			quote->quote_state = true;
			quote->quote = *src;
			*dest++ = *src++;
		}
		else if (*src == quote->quote && quote->quote_state)
		{
			quote->quote = 0;
			quote->quote_state = false;
			*dest++ = *src++;
		}
		else
			*dest++ = *src++;
	}
	*dest = '\0';
}

/// @brief This function removes the whitespaces from
/// a string and replaces them for the a \1 char. It
/// null terminates the destination.
/// @param dest 
/// @param src 
/// @param quote 
void	remove_whitespaces(char *str, t_quotes_system *quote)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		quotes_iterator(quote, str[index]);
		if (ft_isspace(str[index]) && !quote->quote_state)
			str[index] = PARSER_SEP;
		index++;
	}
}

/// @brief This function substitutes the valid quotes inside of the prompt
/// for a `\2` in case of the `double quote(\")` and for a `\3` if the valid
/// quote is a `single quote(\')`.
/// @param new_prompt 
/// @param quote 
void	subsquote(char *new_prompt, t_quotes_system *quote)
{
	while (*new_prompt)
	{
		if (*new_prompt == '\'' && !quote->quote_state)
		{
			quote->quote = *new_prompt;
			*new_prompt = SINGLE_QUOTE;
			quote->quote_state = true;
		}
		else if (*new_prompt == '\"' && !quote->quote_state)
		{
			quote->quote = *new_prompt;
			*new_prompt = DOUBLE_QUOTE;
			quote->quote_state = true;
		}
		else if (*new_prompt == quote->quote && quote->quote_state)
		{
			if (*new_prompt == '\'')
				*new_prompt = SINGLE_QUOTE;
			else
				*new_prompt = DOUBLE_QUOTE;
			quote->quote_state = false;
			quote->quote = 0;
		}
		new_prompt++;
	}
}
