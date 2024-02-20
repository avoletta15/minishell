/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:08:05 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/20 16:44:35 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function checks if the given command is a builtin
/// and returns its corresponding enum value, else zero.
/// @param cmd 
/// @return `t_builtin_types(ENUM)`
t_builtin_types	is_builtin(char *cmd)
{
	if (!ft_strncmp(ECHO, cmd, ft_strlen(cmd)))
		return (ECHO_ID);
	if (!ft_strncmp(CD, cmd, ft_strlen(cmd)))
		return (CD_ID);
	if (!ft_strncmp(PWD, cmd, ft_strlen(cmd)))
		return (PWD_ID);
	if (!ft_strncmp(EXPORT, cmd, ft_strlen(cmd)))
		return (EXPORT_ID);
	if (!ft_strncmp(UNSET, cmd, ft_strlen(cmd)))
		return (UNSET_ID);
	if (!ft_strncmp(ENV, cmd, ft_strlen(cmd)))
		return (ENV_ID);
	if (!ft_strncmp(EXIT, cmd, ft_strlen(cmd)))
		return (EXIT_ID);
	return (0);
}

/// @brief This function checks if there's only one command
/// and is a builtin.
/// @param cmd 
/// @return `bool(true or false)`
bool	is_a_single_builtin(t_command *cmd)
{
	return (!cmd->next && is_builtin(*(cmd->args)));
}

/// @brief This function checks which builtin should be executed
/// and runs it with the given arguments.
/// @param args 
void	parent_excution(char **args)
{
	t_builtin_types	builtin_checker;
	t_env			*envs;

	builtin_checker = is_builtin(*args);
	envs = env_api()->env_head;
	if (builtin_checker == ECHO_ID)
		echo(++args);
	else if (builtin_checker == CD_ID)
		cd(++args, envs);
	else if (builtin_checker == PWD_ID)
		pwd();
	else if (builtin_checker == ENV_ID)
		env(envs);
	else if (builtin_checker == EXPORT_ID)
		export(++args);
}

void	mini_executor(t_command *cmds)
{
	if (is_a_single_builtin(cmds))
		parent_excution(cmds->args);
}
