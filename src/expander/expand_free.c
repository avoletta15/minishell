/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:32:52 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/11 10:57:30 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function joins strings and free the original ones.
/// (Build outside the orignal scope because of Norminette requirements).
/// @param test 
/// @param i 
/// @param temp 
/// @param terminal 
/// @return 
char	*ft_join_free(char *test, int i, char *temp, t_terminal *terminal)
{
	char	*var_key;
	free(temp);
	temp = test;
	var_key = ft_strjoin(temp, ft_substr(terminal->tokens->token, i, ft_strlen(terminal->tokens->token)));
	return(var_key);
}

/// @brief This funtions protects in case of a NULL string
/// is returned.
/// (Build outside the orignal scope because of Norminette requirements).
/// @param terminal 
/// @param expand_var 
void	ft_protection_free(t_terminal *terminal, char *var)
{
	free(var);
	free(terminal->prompt);
	free_terminal(terminal);
	malloc_error();
	exit(EXIT_FAILURE);
}