/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 08:31:58 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/14 10:35:14 by arabelo-         ###   ########.fr       */
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
	if (!env_api()->new_env_var("SHLVL=1"))
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
		if (!env_api()->new_env_var("SHLVL=1"))
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

/// @brief This function runs through the environment list and
/// displays each one of node's content if the value is not NULL.
/// @param env 
void	env(t_env *env, int out, unsigned char *exit_status)
{
	visualize_env(env, out);
	*exit_status = 0;
}
