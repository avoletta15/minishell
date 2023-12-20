/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:50:20 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/20 15:51:49 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_whitespaces(char *prompt)
{
	bool	quote_state;
	char	quote;
	size_t	index;
	char	*new_prompt;

	quote_state = false;
	quote = 0;
	index = 0;
	new_prompt = (char *)malloc(sizeof(char) * ft_strlen(prompt) + 1);
	if (!new_prompt)
		return (NULL);
	while (prompt[index])
	{
		if (ft_isspace(prompt[index]) && !quote_state)
			new_prompt[index] = PARSER_SEP;
		else if ((prompt[index] == '\'' || prompt[index] == '\"') && !quote_state)
		{
			quote_state = true;
			quote = prompt[index];
		}
		else if (prompt[index] == quote && quote_state)
		{
			quote_state = false;
			quote = 0;
		}
		else
			new_prompt[index] = prompt[index];
		index++;
		// else if (ft_isspace(prompt[index]) && quote_state)
		// 	new_prompt[index] = prompt[index];
	}
	prompt[index] = '\0';
	return (prompt);
}
