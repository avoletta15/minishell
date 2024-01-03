/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:38:52 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/03 16:47:26 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function allocates memory for a
/// args struct and change the ownership of the given
/// token's string to it, then points next pointer to NULL
/// and give it the token's id and returns the allocated memory.
/// @param token 
/// @return 
t_args	*create_args(t_token *token)
{
	t_args	*arg;

	arg = (t_args *)malloc(sizeof(t_args));
	if (!arg)
		return (NULL);
	arg->args = token->token;
	arg->toked_id = token->token_id;
	arg->next = NULL;
	token->token = NULL;
	return (arg);
}

/// @brief This function allocates memory for a
/// redirect struct and change the ownership of the given
/// token next struct's string to it, then points next pointer
// to NULL and give it the token's id and returns the allocated memory.
/// @param token 
/// @return 
t_redirect	*create_redirect(t_token *token)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->content = token->next->token;
	redirect->toked_id = token->token_id;
	redirect->next = NULL;
	token->next->token = NULL;
	return (redirect);
}

/// @brief This function adds a create arg to the
/// args list from terminal. If at any point the
/// memory allocation fails, the free_struct function
/// is called and all previously allocated memory
/// is deallocated, then the process exits.
/// @param terminal 
/// @param token 
void	add_arg(t_terminal *terminal, t_token *token)
{
	t_args	*arg;

	if (!terminal->args)
	{
		terminal->args = create_args(token);
		if (!terminal->args)
			free_structs(terminal, true, &malloc_error);
		return ;
	}
	arg = terminal->args;
	while (arg->next)
		arg = arg->next;
	arg->next = create_args(token);
	if (!arg->next)
		free_structs(terminal, true, &malloc_error);
}

/// @brief This function adds a create redirect to the
/// redirect list from terminal. If at any point the
/// memory allocation fails, the free_struct function
/// is called and all previously allocated memory
/// is deallocated, then the process exits.
/// @param terminal 
/// @param token 
void	add_redirect(t_terminal *terminal, t_token *token)
{
	t_redirect	*redirect;

	if (!terminal->redirects)
	{
		terminal->redirects = create_redirect(token);
		if (!terminal->redirects)
			free_structs(terminal, true, &malloc_error);
		return ;
	}
	redirect = terminal->redirects;
	while (redirect->next)
		redirect = redirect->next;
	redirect->next = create_redirect(token);
	if (!redirect->next)
		free_structs(terminal, true, &malloc_error);
}
