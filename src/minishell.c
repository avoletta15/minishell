/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/29 19:56:14 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_terminal terminal)
{
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
		parser(&terminal);
		// ft_expansion_check_refac(&terminal, 0);
		set_cmds_path(&terminal);
		mini_executor(&terminal);
		// visualize_commands(terminal.commands);
		free_structs(&terminal, false, NULL);
		reset_terminal(&terminal, SUCCESS);
	}
}

int	main(int ac, char **av, char **env_path)
{
	t_terminal	terminal;
	int			i;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	i = -1;
	init_terminal(&terminal, true);
	env_api()->len = 0;
	while (env_path && env_path[++i])
		terminal.env = env_structure(env_path[i], terminal.env);
	if (!init_env(&terminal))
		return (0);
	init_shell(terminal);
	free_env_list(&terminal.env);
	return (0);
}
