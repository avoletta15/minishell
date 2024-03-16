/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:15 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/16 15:33:19 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_command(t_command *command)
{
	printf("	{\n");
	printf("		command's struct address: %p,\n", command);
	printf("		command's path: %s,\n", command->cmd_path);
	printf("		command's fd: [%i, %i],\n",
		command->pipe_fd[0], command->pipe_fd[1]);
	printf("		command's std_fd: { %i, %i },\n",
		command->std_fds.in, command->std_fds.out);
	print_args(command->args);
	print_redir(command->redirections);
	printf("		prev: %p,\n", command->prev);
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

void	visualize_env(t_env *env, int out)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, out);
			ft_putstr_fd("=", out);
			ft_putendl_fd(env->value, out);
		}
		env = env->next;
	}
}

void	print_str(char *str)
{
	while (str && *str)
	{
		if (*str == PARSER_SEP)
			printf("\\1");
		else if (*str == SINGLE_QUOTE)
			printf("\\3");
		else if (*str == DOUBLE_QUOTE)
			printf("\\2");
		else
			printf("%c", *str);
		str++;
	}
}
