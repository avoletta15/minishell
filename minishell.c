/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/23 15:51:23 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env_path)
{
	t_program	program;
	int			i;

	(void)ac;
	(void)av;
	(void)env_path;
	init_program(&program);
	while (1)
	{
		i = 0;
		program.quotes_system.prompt = readline("minishell>");
		lexer(&program.quotes_system);
		if (!program.quotes_system.prompt)
			continue ;
		while (program.quotes_system.prompt[i])
		{
			if (program.quotes_system.prompt[i] == PARSER_SEP)
				write(1, "\\1", 2);
			else
				write(1, &program.quotes_system.prompt[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
	return (0);
}
