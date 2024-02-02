/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/02 11:55:39 by arabelo-         ###   ########.fr       */
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
		mini_executor(terminal.commands);
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
	// while(env && env->next)
	// {
	// 	printf("\n[\n%s\n", env->info);
	// 	printf("%p]", env);
	// 	env = env->next;
	// }
	init_terminal(&terminal, true);
	terminal.env = env;
	init_shell(terminal);
	free_env_list(&env);
	return (0);
}
