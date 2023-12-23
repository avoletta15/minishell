/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/23 17:17:33 by arabelo-         ###   ########.fr       */
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
		if (!lexer(&program.quotes_system))
			continue ;
		while (program.quotes_system.prompt_splitted[i])
		{
			// if (program.quotes_system.prompt[i] == PARSER_SEP)
			// 	write(1, "\\1", 2);
			// else
			// 	write(1, &program.quotes_system.prompt[i], 1);
			printf("%s\n", program.quotes_system.prompt_splitted[i++]);
		}
		i = 0;
		while (program.quotes_system.prompt_splitted[i])
			free(program.quotes_system.prompt_splitted[i++]);
		free(program.quotes_system.prompt_splitted);
	}
	return (0);
}
