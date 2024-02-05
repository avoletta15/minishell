/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 08:31:58 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/04 17:41:44 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_pwd_value(t_env *env)
{
	char	*real_cwd;

	real_cwd = getcwd(NULL, 0);
	if (!real_cwd)
	{
		write(2, "minishell: error: couldn't get cwd\n", 35);
		return (false);
	}
	if (!ft_strncmp(env->info, real_cwd, ft_strlen(real_cwd)))
	{
		free(real_cwd);
		return (true);
	}
	free(env->info);
	env->info = ft_strjoin("PWD=", real_cwd);
	if (!env->info)
		return (malloc_error(), false);
	return (true);
}

bool	check_minimum_env_set(t_env *env)
{
	int		i;
	char	*key;

	i = 0;
	while (env->info[i] && env->info[i] != '=')
		i++;
	if (env->info[i] == '=')
	{
		key = ft_substr(env->info, 0, i - 1);
		if (!key)
		{
			malloc_error();
			return (false);
		}
	}
	if (!ft_strncmp(key, "PWD", ft_strlen("PWD")))
		return (free(key), check_pwd_value(env));
}

bool	build_minimum_env(t_env *env)
{
	char	*pwd;
	char	*var;
	t_env	*new_env_node;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (malloc_error(), false);
	var = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!var)
		return (malloc_error(), false);
	env = new_node(var);
	free(var);
	if (!env)
		return (malloc_error(), false);
	new_env_node = new_node("SHLVL=1");
	if (!new_env_node)
		return (malloc_error(), false);
	add_node_tail(&env, new_env_node);
	new_env_node = new_node("OLDPWD");
	if (!new_env_node)
		return (malloc_error(), false);
	add_node_tail(&env, new_env_node);
}

bool	env_build(t_env *env)
{
	if (!env)
	{
		if (!build_minimum_env(env))
			return (false);
		return (true);
	}
	while (env)
	{

	}
}

/// @brief This function runs through the environment list and
/// displays each one of node's content.
/// @param env 
void	env(t_env *env)
{
	visualize_env(env);
}
