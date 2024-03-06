/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:06:09 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/05 11:12:03 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/// @brief This function tries to change the current working directory
/// to the given directory's path. On error it displays an error
/// message in the stderr and sets the exit status to 1. On success
/// it sets the exit status to 0. Returns true on success, else false.
/// @param dir_path 
/// @param exit_status 
/// @return 
bool	change_dir(char *dir_path, unsigned char *exit_status)
{
	int		res;
	t_env	*home;

	if (!*dir_path)
	{
		home = getvar("HOME");
		if (!home)
		{
			*exit_status = 1;
			write(2, CD_HOME_NOT_FOUND_ERROR,
				ft_strlen(CD_HOME_NOT_FOUND_ERROR));
			return (false);
		}
		res = chdir(home->value);
	}
	else
		res = chdir(dir_path);
	if (res == -1)
	{
		*exit_status = 1;
		return (cd_fail(dir_path));
	}
	*exit_status = 0;
	return (true);
}

/// @brief This function changes the current working directory to
/// the given directory's path. On error it displays an
/// error message in the stderr.
/// @param dir_path 
void	cd(char **dir_path, unsigned char *exit_status)
{
	if (size_of_array(dir_path) > 1)
	{
		*exit_status = 1;
		cd_args_count_error();
		return ;
	}
	if (!change_dir(*dir_path, exit_status))
		return ;
	if (!setpwds(getvar("OLDPWD"), getvar("PWD"), getcwd(NULL, 0)))
	{
		malloc_error();
		return ;
	}
	return ;
}
