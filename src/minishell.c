/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/13 21:09:20 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function parses the prompt, and if it is valid
/// it calls the lexer, parser, expander, and the heredoc. On error
/// it retunrs false and does not allow the execution of the command.
/// @param terminal 
/// @return 
static bool	parsing_shell(t_terminal *terminal)
{
	if (!terminal->prompt)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		return (false);
	}
	if (!ft_strlen(terminal->prompt))
	{
		reset_terminal(terminal);
		return (false);
	}
	if (!lexer(terminal))
		return (false);
	parser(terminal);
	set_cmds_path(terminal);
	ft_expansion(terminal, 0);
	set_cmds_path(terminal);
	handle_parent_execution_signals();
	if (!here_doc(terminal))
		return (false);
	return (true);
}

/// @brief This function initializes the shell and starts the loop
/// that will keep the shell running until the user exits or some
/// critical error happens.
/// @param terminal 
void	init_shell(t_terminal *terminal)
{
	while (1)
	{
		terminal->prompt = readline("minishell> ");
		if (parsing_shell(terminal))
			mini_executor(terminal);
		else
			close_cmds_fds(terminal->commands, false);
		handle_parent_signals();
		free_structs(terminal, false, NULL);
		reset_terminal(terminal);
	}
}

int	main(int ac, char **av, char **env_path)
{
	t_terminal	*terminal;
	int			i;

	(void)av;
	terminal = get_terminal();
	if (ac != 1)
		exit(EXIT_FAILURE);
	i = -1;
	init_terminal(terminal);
	handle_parent_signals();
	terminal->env = NULL;
	env_api()->len = 0;
	while (env_path && env_path[++i])
		terminal->env = env_structure(env_path[i], terminal->env);
	if (!init_env(terminal))
		exit(EXIT_FAILURE);
	init_shell(terminal);
	free_terminal(terminal);
	return (0);
}
