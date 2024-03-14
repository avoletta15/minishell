/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:33:33 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/13 20:35:40 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function executes the command using the execve function. On
/// success, the function does not return. On failure, the function prints an
/// error message and exits the child program.
/// @param terminal 
/// @param cmd 
void	chose_execve(t_terminal *terminal, t_command *cmd)
{
	execve(cmd->cmd_path, cmd->args, convert_env_list_to_array());
	close_cmds_fds(terminal->commands, true);
	free_terminal(terminal);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	perror("minishell");
	exit(EXIT_FAILURE);
}
