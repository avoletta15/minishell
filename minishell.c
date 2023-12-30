/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/30 17:13:55 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env_path)
{
	t_program	program;

	(void)ac;
	(void)av;
	(void)env_path;
	init_program(&program, true);
	while (1)
	{
		program.prompt = readline("minishell>");
		if (!ft_strlen(program.prompt))
		{
			reset_program(&program, true);
			continue ;
		}
		if (!lexer(&program))
			continue ;
		visualize_tokens(program.tokens);
		free_tokens(program.tokens);
		reset_program(&program, false);
	}
	return (0);
}
