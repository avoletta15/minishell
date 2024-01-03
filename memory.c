/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:47:23 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/03 16:53:38 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	visualize_tokens(terminal->tokens);
	free_tokens(terminal->tokens);
}
