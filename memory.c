/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:47:23 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/30 17:31:01 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function deallocates all memory dynamically allocated
/// for the project.
/// @param terminal 
/// @param call_back 
void	free_project(t_terminal *terminal, void (*call_back)(void))
{
	if (call_back)
		call_back();
	if (terminal->prompt)
	{
		free(terminal->prompt);
		terminal->prompt = NULL;
	}
}

/// @brief This function deallocates the array of strings used to parse
/// the user prompt.
/// @param prompt_splitted 
void	free_prompt(char **prompt_splitted)
{
	int	i;

	i = 0;
	while (prompt_splitted && prompt_splitted[i])
		free(prompt_splitted[i++]);
	free(prompt_splitted);
}

/// @brief This function deallocates all tokens.
/// @param tokens 
void	free_tokens(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		curr = tokens->next;
		free(tokens->token);
		free(tokens);
		tokens = curr;
	}
}
