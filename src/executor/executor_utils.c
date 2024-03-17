/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:33:33 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/17 16:47:08 by marioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function executes the command using the execve function. On
/// success, the function does not return. On failure, the function prints an
/// error message and exits the child program.
/// @param terminal 
/// @param cmd 
void	choose_execve(t_terminal *terminal, t_command *cmd)
{
	char		**env;

	env = convert_env_list_to_array();
	execve(cmd->cmd_path, cmd->args, env);
	close_cmds_fds(terminal->commands, true);
	free_array(env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	perror("minishell");
	if (access(cmd->cmd_path, F_OK) == -1)
	{
		free_terminal(terminal);
		exit(NOT_FOUND);
	}
	if (access(cmd->cmd_path, X_OK) == -1)
	{
		free_terminal(terminal);
		exit(NOT_EXECUTABLE);
	}
	free_terminal(terminal);
	exit(NOT_EXECUTABLE);
}
