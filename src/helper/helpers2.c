/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:15 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/17 16:04:37 by marioliv         ###   ########.fr       */
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

void	print_quote_system(t_quotes_system *quote)
{
	printf("{\n");
	if (quote->quote_state)
		printf("	quote_state: %s,\n", "true");
	else
		printf("	quote_state: %s,\n", "false");
	printf("	quote: %c,\n", quote->quote);
	printf("	quote_value: %i,\n", quote->quote);
	if (quote->was_quoted)
		printf("	was_quoted: %s,\n", "true");
	else
		printf("	was_quoted: %s,\n", "false");
	printf("	quote final index: %li\n", quote->i);
	printf("}\n");
}
