/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:08:05 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/04 08:29:16 by arabelo-         ###   ########.fr       */
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
void	parent_excution(char **args, t_env *environ)
{
	t_builtin_types	builtin_cheker;

	builtin_cheker = is_builtin(*args);
	if (builtin_cheker == ECHO_ID)
		echo(++args);
	else if (builtin_cheker == CD_ID)
		cd(++args);
	else if (builtin_cheker == PWD_ID)
		pwd();
	else if (builtin_cheker == ENV_ID)
		env(environ);
}

void	mini_executor(t_command *cmds, t_env *env)
{
	if (is_a_single_builtin(cmds))
		parent_excution(cmds->args, env);
}
