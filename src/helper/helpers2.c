/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:15 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/04 10:14:11 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_command(t_command *command)
{
	printf("	{\n");
	printf("		command's struct address: %p,\n", command);
	printf("		command's path: %s,\n", command->cmd_path);
	printf("		command's fd: [%i, %i],\n",
		command->fd[0], command->fd[1]);
	print_args(command->args);
	print_redir(command->redirections);
	printf("		next: %p\n", command->next);
	printf("	}");
}

void	visualize_commands(t_command *command)
{
	int	i;

	if (!command)
		return ;
	printf("[\n");
	i = 0;
	while (command)
	{
		printf("%i -> ", i++);
		printf_command(command);
		if (command->next)
			printf(",\n");
		else
			printf("\n");
		command = command->next;
	}
	printf("]\n");
}