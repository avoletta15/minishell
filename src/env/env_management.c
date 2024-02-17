/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:56:55 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/02/17 19:09:38 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function initializes the environment API.
/// @param env_head 
bool	init_env(t_terminal *terminal)
{
	env_api()->new_env_var = &new_env_var;
	env_api()->new_env_key_value = &new_env_key_value;
	env_api()->getvar = &getvar;
	if (!build_minimum_env(terminal))
	{
		// free everything and exit
		return (false);
	}
	return (true);
}

/// @brief This function returns an `\"environment application programming
/// interface\"`, which can be used to manipulate the enviroment.
/// @param  
/// @return `t_env_api`
t_env_api	*env_api(void)
{
	static	t_env_api	api;

	return (&api);
}
