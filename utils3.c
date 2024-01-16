/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:50:57 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/16 14:51:06 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, ECHO, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, CD, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, PWD, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, EXPORT, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, UNSET, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, ENV, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, EXIT, ft_strlen(cmd)))
		return (true);
	return (false);
}

void	verify_cmd_path(t_terminal *terminal)
{
	t_command	*cmd;

	cmd = terminal->commands;
	while (cmd)
	{
		if (ft_strchr(cmd->args[0], '/') || is_builtin(cmd->args[0]))
			cmd->cmd_path = cmd->args[0];
		cmd = cmd->next;
	}
}

char	*bind_paths(t_terminal *terminal, char *cmd)
{
	char	**paths;
	char	*path;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		free_structs(terminal, true, &malloc_error);
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		if (!path)
			free_structs(terminal, true, &malloc_error);
		path = gnl_strjoin(path, cmd);
		if (!path)
			free_structs(terminal, true, &malloc_error);
		if (!access(path, F_OK))
			return (path);
		free(path);
		paths++;
	}
	return (NULL);
}

void	get_absolute_path(t_terminal *terminal)
{
	t_command	*cmd;
	char		*res;

	cmd = terminal->commands;
	while (cmd)
	{
		if (!cmd->cmd_path)
		{
			res = bind_paths(terminal, cmd->args[0]);
			if (res)
			{
				cmd->cmd_path = res;
				free(cmd->args[0]);
				cmd->args[0] = cmd->cmd_path;
			}
		}
		cmd = cmd->next;
	}
}

void	find_paths(t_terminal *terminal)
{
	verify_cmd_path(terminal);
	get_absolute_path(terminal);
}
