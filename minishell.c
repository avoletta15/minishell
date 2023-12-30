/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/30 17:31:56 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env_path)
{
	t_terminal	terminal;

	(void)ac;
	(void)av;
	(void)env_path;
	init_program(&terminal, true);
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
	return (0);
}
