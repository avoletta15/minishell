/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/27 23:40:55 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env_path)
{
	t_terminal	terminal;

	(void)ac;
	(void)av;
	terminal.env = env_path;
	init_terminal(&terminal, true);
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
		visualize_tokens(terminal.tokens);
		// parser(&terminal);
		// visualize_commands(terminal.commands);
		// free_structs(&terminal, false, NULL);
		reset_terminal(&terminal, SUCCESS);
	}
	return (0);
