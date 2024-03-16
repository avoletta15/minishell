/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:41:06 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/16 14:34:05 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	printf("	{\n");
	printf("		token_id: %i,\n", token->token_id);
	printf("		token: %s,\n", token->token);
	printf("		prev: %p,\n", token->prev);
	printf("		next: %p,\n", token->next);
	printf("	}");
}

void	visualize_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	printf("[\n");
	while (tokens)
	{
		print_token(tokens);
		if (tokens->next)
			printf(",\n");
		else
			printf("\n");
		tokens = tokens->next;
	}
	printf("]\n");
}

void	print_args(char **args)
{
	printf("		command's args: [ ");
	while (args && *args)
	{
		if (*(args + 1))
			printf("%s, ", *args);
		else
			printf("%s ", *args);
		args++;
	}
	printf("],\n");
}

void	print_redir(t_redirect *redirect)
{
	printf("		command's redirections: ");
	while (redirect)
	{
		printf("{ token_id: %i, content: %s, fd: %d, invalid_expansion: %s } -> ",
			redirect->toked_id, redirect->content, redirect->fd, redirect->invalid_expansion ? "true" : "false");
		redirect = redirect->next;
	}
	printf("NULL,\n");
}
