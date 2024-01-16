/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/16 19:46:36 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	init_shell(t_terminal terminal)
{
	// int	i = 0;
	while (1)
	{
		// if (i++ == 2)
		// 	return (0);
		terminal.prompt = readline("minishell>");
		if (!ft_strlen(terminal.prompt))
		{
			reset_terminal(&terminal, true);
			continue ;
		}
		if (!lexer(&terminal))
			continue ;
		parser(&terminal);
		visualize_commands(terminal.commands);
		free_structs(&terminal, false, NULL);
		reset_terminal(&terminal, SUCCESS);
	}
}


int	main(int ac, char **av, char **env_path)
{
	t_terminal	terminal;
	t_env		*env;
	env = NULL;
	int			i;
	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;
	i = -1;
	while(env_path && env_path[++i])
		env = env_structure(env_path[i], env);
	while(env && env->next)
	{
		printf("\n[\n%s\n", env->info);
		printf("%p]", env);
		env = env->next;
	}
	init_terminal(&terminal, true);
	init_shell(terminal);
	free_env_list(&env);
	return (0);
}
