/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:53:34 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/22 11:56:03 by arabelo-         ###   ########.fr       */
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
/// explaining the user the error about bad syntax.
void	bad_syntax_error(void)
{
	write(2, BAD_SYNTAX_ERROR, ft_strlen(BAD_SYNTAX_ERROR));
}
