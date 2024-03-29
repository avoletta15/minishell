/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 06:18:26 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/05 11:01:51 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function classifies the given token by an id.
/// @param token 
/// @return 
int	get_token_id(char *token)
{
	if (!ft_strncmp(token, PIPE, ft_strlen(PIPE)))
		return (PIPE_ID);
	if (!ft_strncmp(token, APPEND, ft_strlen(APPEND)))
		return (APPEND_ID);
	if (!ft_strncmp(token, HERE_DOC, ft_strlen(HERE_DOC)))
		return (HERE_DOC_ID);
	if (!ft_strncmp(token, INPUT_REDIRECT, ft_strlen(INPUT_REDIRECT)))
		return (INPUT_REDIRECT_ID);
	if (!ft_strncmp(token, OUTPUT_REDIRECT, ft_strlen(OUTPUT_REDIRECT)))
		return (OUTPUT_REDIRECT_ID);
	return (ARGS_ID);
}

/// @brief This function allocates memory for a
/// token struct and for its string, then points
/// the prev and next pointer to NULL and give it
/// an id and returns the allocated memory.
/// @param token 
/// @return 
t_token	*create_token(char *token)
{
	t_token	*token_infos;

	token_infos = (t_token *)malloc(sizeof(t_token));
	if (!token_infos)
		return (NULL);
	token_infos->token = ft_strdup(token);
	if (!token_infos->token)
	{
		free(token_infos);
		return (NULL);
	}
	token_infos->token_id = get_token_id(token);
	token_infos->next = NULL;
	token_infos->prev = NULL;
	return (token_infos);
}

/// @brief This function appends the given token
/// into the given liked list.
/// @param tokens 
/// @param new_token 
void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*curr_token;

	if (!tokens || !*tokens)
	{
		*tokens = new_token;
		return ;
	}
	curr_token = *tokens;
	while (curr_token->next)
		curr_token = curr_token->next;
	new_token->prev = curr_token;
	curr_token->next = new_token;
}

/// @brief This function transforms the given array
/// of strings into a linked list of tokens.
/// @param terminal
/// @param tokens 
void	tokenize_prompt(t_terminal *terminal, t_token **tokens)
{
	t_token	*curr;
	char	**prompt_splitted;
	int		i;

	prompt_splitted = terminal->prompt_splitted;
	i = 0;
	while (prompt_splitted && prompt_splitted[i])
	{
		curr = create_token(prompt_splitted[i]);
		if (!curr)
		{
			malloc_error();
			free_array(prompt_splitted);
			free_tokens(*tokens);
			exit(EXIT_FAILURE);
		}
		add_token(tokens, curr);
		i++;
	}
	free_array(prompt_splitted);
	terminal->prompt_splitted = NULL;
}
