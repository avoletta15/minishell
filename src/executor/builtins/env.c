/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 08:31:58 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/21 00:40:48 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function builds the minimum environment variables
/// in case the variables are not set up. Returns the begin of 
/// the environment list, on error returns NULL.
/// @param pwd 
/// @return 
t_env	*set_minimum_env(char *pwd)
{
	char	*pwd_copy;

	pwd_copy = ft_strdup(pwd);
	if (!pwd_copy)
		return (NULL);
	if (!env_api()->new_env_key_value("PWD", pwd))
		return (NULL);
	if (!env_api()->new_env_key_value("OLDPWD", pwd_copy))
		return (NULL);
	if (!env_api()->new_env_key_value("SHLVL", "1"))	
		return (NULL);
	return (env_api()->env_head);
}

/// @brief This function updates the min
/// @param pwd 
/// @param shlvl 
/// @return 
bool	update_env(char *pwd, t_env *shlvl)
{
	char	*lvl;

	if (!setpwds(getvar("OLDPWD"), getvar("PWD"), pwd))
	{
		malloc_error();
		return (false);
	}
	if (!shlvl)
	{
		if (!env_api()->new_env_key_value("SHLVL", "1"))	
			return (false);
	}
	else
	{
		lvl = ft_itoa(ft_atoi(shlvl->value) + 1);
		if (!lvl)
			return (false);
		free(shlvl->value);
		shlvl->value = lvl;
	}
	return (true);
}

/// @brief This function build the minimum environment variables
/// when it's not given at the program begin.
/// @param  
/// @return 
bool	build_minimum_env(t_terminal *terminal)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (false);
	if (!terminal->env)
	{
		terminal->env = set_minimum_env(pwd);
		if (!terminal->env)
		{
			free(pwd);
			return (false);
		}
	}
	else
	{
		env_api()->env_head = terminal->env;
		if (!update_env(pwd, getvar("SHLVL")))
			return (false);
	}
	return (true);
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

	while (*str && *str != '=')
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

/// @brief This function runs through the environment list and
/// displays each one of node's content if the value is not NULL.
/// @param env 
void	env(t_env *env)
{
	visualize_env(env);
}
