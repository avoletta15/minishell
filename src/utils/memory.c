/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:47:23 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/05 10:58:59 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function deallocates the array of strings used to parse
/// the user prompt.
/// @param prompt_splitted 
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		free(array[i++]);
	free(array);
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

/// @brief This function deallocates all args.
/// @param arg 
void	free_args(t_args *arg)
{
	t_args	*curr;

	curr = arg;
	while (curr)
	{
		curr = arg->next;
		free(arg->args);
		free(arg);
		arg = curr;
	}
}

/// @brief This function deallocates all redirection.
/// @param redirect 
void	free_redirect(t_redirect *redirect)
{
	t_redirect	*curr;

	curr = redirect;
	while (curr)
	{
		curr = redirect->next;
		free(redirect->content);
		free(redirect);
		redirect = curr;
	}
}

/// @brief This function deallocates all redirections
/// and all args, displays the malloc_error function and exits.
/// @param terminal 
void	free_redir_args(t_terminal *terminal)
{
	free_args(terminal->args);
	free_redirect(terminal->redirects);
	free_tokens(terminal->tokens);
}
