/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:52:59 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/01 16:48:43 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function checks if a given token
/// is a built in command.
/// @param token 
/// @return 
int	is_built_in(char *token)
{
	if (!ft_strncmp(token, ECHO, ft_strlen(ECHO)))
		return (BUILT_IN_ID);
	if (!ft_strncmp(token, CD, ft_strlen(CD)))
		return (BUILT_IN_ID);
	if (!ft_strncmp(token, PWD, ft_strlen(PWD)))
		return (BUILT_IN_ID);
	if (!ft_strncmp(token, EXPORT, ft_strlen(EXPORT)))
		return (BUILT_IN_ID);
	if (!ft_strncmp(token, UNSET, ft_strlen(UNSET)))
		return (BUILT_IN_ID);
	if (!ft_strncmp(token, ENV, ft_strlen(ENV)))
		return (BUILT_IN_ID);
	if (!ft_strncmp(token, EXIT, ft_strlen(EXIT)))
		return (BUILT_IN_ID);
	return (0);
}
