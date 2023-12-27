/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:29:54 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/27 07:56:27 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function copies from src to dest
/// the len bytes given as parameter.
/// @param dest 
/// @param src 
/// @param len 
void	copynstr(char *dest, char *src, size_t len)
{
	while (dest && src && *src && len--)
		*dest++ = *src++;
}

/// @brief This function verifies if the given set
/// of characters is a special one.
/// @param set 
/// @return 
int	is_special_chars(char *set)
{
	size_t	len;

	len = 2;
	if (!ft_strncmp("<<", set, len))
		return (len);
	if (!ft_strncmp(">>", set, len))
		return (len);
	len = 1;
	if (!ft_strncmp("<", set, len))
		return (len);
	if (!ft_strncmp(">", set, len))
		return (len);
	if (!ft_strncmp("|", set, len))
		return (len);
	return (-1);
}

/// @brief This function is one part of the delimit_special_chars
/// function, which puts the separator character between the 
/// special characters, such as pipes and redirects.
/// @param dest 
/// @param src 
/// @param pos 
void	put_separator(char **dest, char **src, int *pos)
{
	**dest = PARSER_SEP;
	(*dest)++;
	copynstr(*dest, *src, *pos);
	*dest += *pos;
	*src += *pos;
	**dest = PARSER_SEP;
	(*dest)++;
}

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
