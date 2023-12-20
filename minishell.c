/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:51:51 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/20 15:51:41 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env_path)
{
	char *str;
	(void)ac;
	(void)av;
	(void)env_path;
	t_program	program;

	init_program(&program);
	while (1)
	{
		str = readline("minishell>");
		printf("original: %s\n", str);
		program.quotes_system.prompt = remove_whitespaces(str);
		printf("no whitespaces: %s\n", program.quotes_system.prompt);
	}
	return (0);
}