/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:21:14 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/11 18:34:13 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function counts how many strings are given.
/// @param strs 
/// @return `size_t(unsigned long)`
size_t	size_of_array(char **strs)
{
	size_t	i;

	i = 0;
	while (strs && strs[i])
		i++;
	return (i);
}

/// @brief This function checks if the given command has an
/// absolute path and returns true if there's, else false.
/// @param str 
/// @return 
bool	check_absolute_path(char *str)
{
	return (ft_strchr(str, '/') != NULL);
}

/// @brief This function searches for the given cmd (binary file)
/// in all available paths and returns the absolute path if
/// it finds a accessable file, else NULL.
/// @param all_paths 
/// @param cmd 
/// @return 
char	*find_path(char **all_paths, char *cmd)
{
	char	*real_path;
	char	*tmp;

	while (all_paths && *all_paths)
	{
		tmp = *all_paths;
		tmp = ft_strjoin(tmp, "/");
		if (!tmp)
			return (NULL);
		real_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!real_path)
			return (NULL);
		if (!access(real_path, F_OK))
			return (real_path);
		free(real_path);
		all_paths++;
	}
	return (NULL);
}

/// @brief This function checks if the given command is
/// a builtin, if so set the cmd->cmd_path to the builtin,
/// else it searches for the environment PATH, if exists
/// it searches for the binary file in all paths, replaces
/// the cmd->cmd_path for the found path, else to Tthe
/// @param cmd 
/// @return 
bool	set_path(t_command *cmd)
{
	t_env	*env;
	char	**all_paths;
	char	*real_path;

	if (!*(cmd->args))
		return (false);
	if (is_builtin(*(cmd->args)))
		return (false);
	env = getvar("PATH");
	if (!env)
		return (false);
	all_paths = ft_split(env->value, ':');
	if (!all_paths)
		return (false);
	real_path = find_path(all_paths, *(cmd->args));
	free_array(all_paths);
	if (!real_path)
		return (true);
	cmd->cmd_path = real_path;
	return (true);
}

/// @brief This function sets an absolute path to each
/// command if the command path has no backslash "/",
/// else it leaves as it is.
/// @param terminal 
void	set_cmds_path(t_terminal *terminal)
{
	t_command	*cmd;

	cmd = terminal->commands;
	while (cmd)
	{
		if (!check_absolute_path(*(cmd->args)))
		{
			if (!set_path(cmd))
				cmd->cmd_path = ft_strdup(*(cmd->args));
		}
		else
			cmd->cmd_path = ft_strdup(*(cmd->args));
		cmd = cmd->next;
	}
}
