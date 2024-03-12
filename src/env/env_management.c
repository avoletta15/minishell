/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:56:55 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/11 19:54:51 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function initializes the environment API.
/// @param env_head 
bool	init_env(t_terminal *terminal)
{
	env_api()->new_env_var = &new_env_var;
	env_api()->new_env_key_value = &new_env_key_value;
	env_api()->update_var = &update_var;
	env_api()->remove_var = &remove_var;
	env_api()->getvar = &getvar;
	if (!build_minimum_env(terminal))
	{
		free_terminal(terminal);
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
	static t_env_api	api;

	return (&api);
}

/// @brief This function checks if the exported variable and
/// its value are valid. Checks unclosed quotes as well, on error
/// returns false, else true.
/// @param str 
/// @return 
bool	check_new_env(char *str)
{
	char	*original;
	char	*equals_sign;
	original = str;

	equals_sign = ft_strchr(original, '=');
	if (equals_sign == str)
		return (false);
	if (!equals_sign)
		equals_sign = original + ft_strlen(original);
	while (original < equals_sign)
	{
		if (!is_var_key_char_valid(*original, original - str))
			return (false);
		original++;
	}
	return (true);
}

/// @brief This function returns the key of the given variable.
/// If there's no equals sign it returns the whole string.
/// If there's any error it returns NULL.
/// @param str 
/// @return 
char	*get_var_key(char *str)
{
	char	*key;
	char	*equals_sign;

	equals_sign = ft_strchr(str, '=');
	if (!equals_sign)
		equals_sign = str + ft_strlen(str);
	key = ft_substr(str, 0, equals_sign - str);
	return (key);
}
