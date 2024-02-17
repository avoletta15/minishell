/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:06:09 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/14 10:06:08 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function searches for the `\"HOME\"` environment variable
/// and returns it if is set, else NULL.
/// @param env 
/// @return 
t_env	*cd_home_checker(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "HOME", ft_strlen(env->key)))
			break ;
		env = env->next;
	}
	if (!env)
	{
		write(2, CD_HOME_NOT_FOUND_ERROR, ft_strlen(CD_HOME_NOT_FOUND_ERROR));
		return (NULL);
	}
	return (env);
}

/// @brief This function sets the value of the enviroment variable
/// `\"OLDPWD\"` if exists, else does deallocates the char * pwd
/// and returns true. If the t_env *envpwd is not set and the value
/// of OLDPWD is NULL it set its value to an empty string.
/// In case t_env *envpwd is not set and the value of OLDPWD is not
/// NULL is set the value of OLDPWD to char *pwd.
/// @param oldpwd 
/// @param envpwd 
/// @param pwd 
/// @return 
bool	setoldpwd(t_env *oldpwd, char *pwd)
{
	if (!oldpwd)
	{
		if (!env_api()->new_env_key_value("OLDPWD", pwd))
			return (malloc_error(), false);
	}
	else
	{
		free(oldpwd->value);
		oldpwd->value = pwd;
	}
	return (true);
}

/// @brief This function updates the `\"PWD\"` environment variable if
/// it exists, else it creates it. On error it returns false, else true.
/// @param envpwd 
/// @return 
bool	setpwd(t_env *envpwd)
{
	char	*curr_pwd;

	curr_pwd = getcwd(NULL, 0);
	if (!curr_pwd)
		return (malloc_error(), false);
	if (!envpwd)
	{
		if (!env_api()->new_env_key_value("PWD", curr_pwd))
		{
			free(curr_pwd);
			malloc_error();
			return (false);
		}
	}
	else
	{
		free(envpwd->value);
		envpwd->value = curr_pwd;
	}
	return (true);
}

/// @brief This function changes the environment variables `\"OLDPWD\" and
/// \"PWD\"` if they exist, else it creates the variables, which
/// does not exist and returns true. On error returns false.
/// @param oldpwd 
/// @param envpwd 
/// @param pwd 
/// @return 
int	setpwds(t_env *oldpwd, t_env *envpwd, char *pwd)
{
	if (!setpwd(envpwd))
	{
		malloc_error();
		return (false);
	}
	if (!setoldpwd(oldpwd, pwd))
	{
		malloc_error();
		return (false);
	}
	return (true);
}

/// @brief This function changes the current working directory to
/// the given directory's path. On error it displays an
/// error message in the stderr.
/// @param dir_path 
bool	cd(char **dir_path, t_env *env)
{
	int		res;
	char	*pwd;

	if (ft_str_count(dir_path) > 1)
		return (cd_args_count_error());
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (malloc_error(), false);
	if (!*dir_path)
	{
		env = cd_home_checker(env);
		if (!env)
			return (false);
		res = chdir(env->value);
	}
	else
		res = chdir(*dir_path);
	if (res == -1)
		return (cd_fail(*dir_path));
	if (!setpwds(getvar("OLDPWD"), getvar("PWD"), pwd))
		return (malloc_error(), false);
	return (true);
}
