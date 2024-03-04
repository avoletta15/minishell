/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:08:05 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/01 19:37:32 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This funcction choses which function to execute.
/// @param terminal 
/// @param cmd 
void	chose_exec(t_terminal *terminal, t_command *cmd)
{
	if (is_builtin(cmd->args[0]))
	{
		exec_builtins(terminal, cmd->args, 1);
		exit(terminal->exit_status);
	}
	else
	{
		if (execve(cmd->cmd_path, cmd->args,
			convert_env_list_to_array()) == -1)
			return (perror("minishell"));
	}
	exit(EXIT_SUCCESS);
}

/// @brief This function calls the redirection_handle function and
/// calls the execve function to execute the command if the command
/// is not a builtin. Else it calls the builtin function inside of the
/// child process.
/// @param cmd 
/// @param in 
/// @param out 
void	child_exec(t_terminal *terminal, t_command *cmd)
{
	bool	should_exec;

	should_exec = true;
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("minishell"));
	if (cmd->pid == 0)
	{
		if (!redirection_handle(cmd, false))
			should_exec = false;
		close_fds(cmd->std_fds.in, cmd->std_fds.out);
		close_fds(cmd->pipe_fd[0], cmd->pipe_fd[1]);
		if (should_exec)
			chose_exec(terminal, cmd);
		exit(errno);
	}
	close_fds(cmd->std_fds.in, cmd->std_fds.out);
}

/// @brief This function executes the pipes and call the child_exec function
/// to execute the commands and wait for the child processes to finish.
/// @param terminal 
/// @param cmd 
void	children_exec(t_terminal *terminal, t_command *cmd)
{
	cmd->std_fds.in = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && pipe(cmd->pipe_fd) == -1)
		{
			perror("minishell");
			break ;
		}
		cmd->std_fds.out = cmd->pipe_fd[1];
		child_exec(terminal, cmd);
		cmd = cmd->next;
		if (cmd)
			cmd->std_fds.in = cmd->prev->pipe_fd[0];
	}
	cmd = terminal->commands;
	while (cmd)
	{
		if (cmd->pid != -1)
			waitpid(cmd->pid, (int *)&terminal->exit_status, 0);
		cmd = cmd->next;
	}
}

/// @brief This is the main function of the executor. It'll call the
/// children_exec function if the command is not a single builtin.
/// @param terminal 
void	mini_executor(t_terminal *terminal)
{
	t_command	*cmd;

	cmd = terminal->commands;
	if (is_a_single_builtin(cmd))
	{
		if (!redirection_handle(cmd, true))
			return ;
		exec_builtins(terminal, cmd->args, cmd->std_fds.out);
		close_fds(cmd->std_fds.in, cmd->std_fds.out);
	}
	else
		children_exec(terminal, cmd);
}
