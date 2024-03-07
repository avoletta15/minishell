/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:20:25 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/07 09:28:35 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function checks which builtin should be executed
/// and runs it with the given arguments.
/// @param args
void	exec_builtins(t_terminal *terminal, char **args, int out)
{
	t_builtin_types	builtin_checker;
	t_env			*envs;

	builtin_checker = is_builtin(*args);
	envs = env_api()->env_head;
	if (builtin_checker == ECHO_ID)
		echo(++args, out, &terminal->exit_status);
	else if (builtin_checker == CD_ID)
		cd(++args, &terminal->exit_status);
	else if (builtin_checker == PWD_ID)
		pwd(out, &terminal->exit_status);
	else if (builtin_checker == ENV_ID)
	{
		if (*(++args))
			return (env_args_count_error(&terminal->exit_status));
		env(envs, out, &terminal->exit_status);
	}
	else if (builtin_checker == EXPORT_ID)
		export(++args, out, &terminal->exit_status);
	else if (builtin_checker == UNSET_ID)
		unset(++args, &terminal->exit_status);
	else if (builtin_checker == EXIT_ID)
		mini_exit(terminal, ++args);
	close_fds(STDIN_FILENO, out);
}
