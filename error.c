/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:53:34 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/29 19:50:02 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function displays a message in the stderr
/// explaining the user the error about malloc.
/// @param  
void	malloc_error(void)
{
	write(2, MALLOC_ERROR, ft_strlen(MALLOC_ERROR));
}

/// @brief This function displays a message in the stderr
/// telling the user about the unclosed quote.
void	unclosed_quote_error(void)
{
	write(2, UNCLOSED_QUOTE_ERROR, ft_strlen(UNCLOSED_QUOTE_ERROR));
}

/// @brief This function displays a message in the stderr
/// explaing the user about the bad syntax error.
/// @param str 
void	bad_syntax_error(char *str)
{
	write(2, BAD_SYNTAX_ERROR1, ft_strlen(BAD_SYNTAX_ERROR1));
	write(2, BAD_SYNTAX_ERROR2, ft_strlen(BAD_SYNTAX_ERROR2));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

/// @brief This function displays an error informing
/// the user about the invalid token syntax sequence.
/// @param program 
/// @param str 
void	invalid_token_error(t_program *program, char *str)
{
	bad_syntax_error(str);
	free_tokens(program->tokens);
	program->tokens = NULL;
}
