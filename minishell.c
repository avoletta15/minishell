/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/11 12:13:41 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	init_shell(t_terminal terminal)
{
	while (1)
	{
		terminal.prompt = readline("minishell>");
		if (!ft_strlen(terminal.prompt))
		{
			reset_terminal(&terminal, true);
			continue ;
		}
		if (!lexer(&terminal))
			continue ;
		visualize_tokens(terminal.tokens);
		free_tokens(terminal.tokens);
		reset_terminal(&terminal, false);
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
	while(env_path[++i])
		env = env_structure(env_path[i], env);
	init_terminal(&terminal, true);
	init_shell(terminal);
	free_env_list(&env);
	return (0);
}
