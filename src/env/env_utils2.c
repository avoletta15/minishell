/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:20:38 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/17 17:07:22 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function creates an new environment variable based on
/// the given environment path, e.g. HOME=/Users/johndoe and inserts it
/// in the t_env linked list. If the allocation fails it displays an error
/// message and returns false, else true.
/// @param env_path 
/// @return 
bool	new_env_var(char *env_path)
{
	t_env	*new_env;

	new_env = new_node(env_path);
	if (!new_env)
		return (malloc_error(), false);
	add_node_tail(&env_api()->env_head, new_env);
	return (true);
}

/// @brief This function creates an new environment variable based on
/// the given environment path, e.g. `\"HOME=/Users/johndoe\"` and inserts it
/// in the t_env linked list. If the allocation fails it displays an error
/// message and returns false, else true.
/// @param env_path 
/// @return 
bool	new_env_key_value(char *key, char *value)
{
	t_env	*new_env;

	new_env = new_node(key);
	if (!new_env)
		return (malloc_error(), false);
	new_env->value = value;
	add_node_tail(&env_api()->env_head, new_env);
	return (true);
}

/// @brief This function searches in the enviroment variables the given
/// variable (char *var) and returns it if this variable is set,
/// else NULL.
/// @param env 
/// @return 
t_env	*getvar(char *var)
{
	t_env	*env;

	env = env_api()->env_head;
	while (env && var)
	{
		if (!ft_strncmp(env->key, var, ft_strlen(env->key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}
