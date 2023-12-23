/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_treatment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:21:05 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/23 15:47:05 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

{

	{
		else
	}
/// @brief This function removes the whitespaces from
/// a string and replaces them for the a \1 char. It
/// null terminates the destination.
/// @param dest 
/// @param src 
/// @param quote 
void	remove_whitespaces(char *dest, char *src, t_quotes_system *quote)
{
	size_t	index;

	index = 0;
	while (src[index])
	{
		if (ft_isspace(src[index]) && !quote->quote_state)
			dest[index] = PARSER_SEP;
		else if ((src[index] == '\'' || src[index] == '\"')
			&& !quote->quote_state)
		{
			quote->quote_state = true;
			quote->quote = src[index];
			dest[index] = src[index];
		}
		else if (src[index] == quote->quote && quote->quote_state)
		{
			quote->quote_state = false;
			quote->quote = 0;
			dest[index] = src[index];
		}
		else
			dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
}
