/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:20:38 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/14 15:09:13 by arabelo-         ###   ########.fr       */
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
	size_t	var_len;
	size_t	len;

	var_len = ft_strlen(var);
	env = env_api()->env_head;
	while (env && var)
	{
		if (var_len > ft_strlen(env->key))
			len = var_len;
		else
			len = ft_strlen(env->key);
		if (!ft_strncmp(env->key, var, len))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/// @brief This function searches for the given environment variable and
/// replaces it if there's an equal sign, else does nothing and returns
/// true. On error returns false.
/// @param env 
/// @param str 
/// @return 
bool	update_var(t_env *env, char *str)
{
	char	*new_value;

	while (str && *str && *str != '=')
		str++;
	if (*str == '=' && env)
	{
		new_value = ft_strdup(++str);
		if (!new_value)
		{
			malloc_error();
			return (false);
		}
		free(env->value);
		env->value = new_value;
	}
	return (true);
}

/// @brief This function deallocates the environment variable
/// from the environment list.
/// @param var 
void	remove_var(char *var)
{
	t_env	*env;

	env = getvar(var);
	if (!env)
		return ;
	if (env->previous)
		env->previous->next = env->next;
	if (env->next)
		env->next->previous = env->previous;
	if (env == env_api()->env_head)
		env_api()->env_head = env->next;
	free(env->key);
	free(env->value);
	env->previous = NULL;
	env->next = NULL;
	free(env);
}
