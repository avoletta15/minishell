/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/05 22:38:37 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_terminal terminal)
{
	build_minimum_env(terminal.env);
	while (1)
	{
		terminal.prompt = readline("minishell> ");
		if (!ft_strlen(terminal.prompt))
		{
			reset_terminal(&terminal, true);
			continue ;
		}
		if (!lexer(&terminal))
			continue ;
		//visualise_expanded_var(&terminal);
		parser(&terminal);
		visualize_commands(terminal.commands);
		ft_expansion_check_refac(&terminal, 0);
		visualize_commands(terminal.commands);
		mini_executor(terminal.commands, terminal.env);
		free_structs(&terminal, false, NULL);
		reset_terminal(&terminal, SUCCESS);
	}
}

int	main(int ac, char **av, char **env_path)
{
	t_terminal	terminal;
	t_env		*env;
	int			i;

	(void)av;
	env = NULL;
	if (ac != 1)
		exit(EXIT_FAILURE);
	i = -1;
	while (env_path && env_path[++i])
		env = env_structure(env_path[i], env);
	// visualize_env(env);
	init_terminal(&terminal, true);
	terminal.env = env;
	init_shell(terminal);
	free_env_list(&env);
	return (0);
}
