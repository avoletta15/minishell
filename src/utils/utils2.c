/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:39:39 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/28 17:13:21 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This funciton verifies if the given
/// token id belongs to a redirection token.
/// @param token_id 
/// @return 
bool	is_redirect_token(t_token_types token_id)
{
	return (token_id >= INPUT_REDIRECT_ID && token_id <= PIPE_ID);
}

/// @brief This functio verifies if the given token
/// has a next token and if it is a redirection.
/// @param token 
/// @return 
bool	is_token_sequence_invalid(t_token *token)
{
	return (is_redirect_token(token->token_id)
		&& token->next && is_redirect_token(token->next->token_id));
}

/// @brief This function verifies if the given token
/// is a pipe and if there is an previous token.
/// @param token 
/// @return 
bool	is_pipe_sequence_invalid(t_token *token)
{
	return (token->token_id == PIPE_ID && !token->prev);
}

/// @brief This function verifies if the given token is
/// a redirection and if there is a next token.
/// @param token 
/// @return 
bool	is_redirect_invalid(t_token *token)
{
	return (is_redirect_token(token->token_id) && !token->next);
}

/// @brief This function verifies if the tokens syntax is correct.
/// @param terminal 
/// @return 
bool	tokens_checker(t_terminal *terminal)
{
	t_token	*tokens;

	tokens = terminal->tokens;
	terminal->exit_status = 2;
	while (tokens)
	{
		if (is_token_sequence_invalid(tokens))
			return (invalid_token_error(terminal, tokens->next->token), false);
		if (is_pipe_sequence_invalid(tokens))
			return (invalid_token_error(terminal, tokens->token), false);
		if (is_redirect_invalid(tokens))
			return (invalid_token_error(terminal, NEW_LINE), false);
		if (!ft_strncmp(tokens->token, ";", ft_strlen(";")))
			return (invalid_token_error(terminal, NEW_LINE), false);
		tokens = tokens->next;
	}
	terminal->exit_status = 0;
	return (true);
}
