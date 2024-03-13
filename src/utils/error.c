/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:53:34 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/13 11:40:02 by arabelo-         ###   ########.fr       */
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
/// @param terminal 
/// @param str 
void	invalid_token_error(t_terminal *terminal, char *str)
{
	bad_syntax_error(str);
	free_tokens(terminal->tokens);
	terminal->tokens = NULL;
	terminal->exit_status = BAD_SYNTAX;
}

/// @brief This function displays an error about
/// the unknow file or directory when no PATH is set.
/// @param str 
void	no_path_error(char *str)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, NO_SUCH_FILE_OR_DIR, ft_strlen(NO_SUCH_FILE_OR_DIR));
}
