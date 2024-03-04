/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:44:20 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/01 19:18:34 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function removes the given variables from the environment
/// list if they exists.
/// @param args 
void	unset(char **args, unsigned char *exit_status)
{
	while (*args)
		env_api()->remove_var(*args++);
	*exit_status = 0;
}
