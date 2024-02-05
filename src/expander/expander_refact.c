/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_refact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:44:44 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/02/05 10:14:01 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expansion_check_refac(t_terminal *terminal, char flag)
{
	// t_command	*save;
	int			i;

	i = -1;
	// save = terminal->commands;
	ft_init_vars(terminal);
	while(terminal->commands->args && terminal->commands->args[++i])
	{
		while(terminal->commands->args[i][terminal->vars.i])
		{
			if(ft_checking_quotes(terminal->commands->args[i], flag, &terminal->vars.i) == SINGLE_QUOTE)
			{
				terminal->vars.var_key = ft_substr(terminal->commands->args[i], terminal->vars.j, terminal->vars.i);
				if (!terminal->vars.var_key)
					ft_protection_free(terminal, terminal->vars.var_key);
				if(terminal->commands->args[i][terminal->vars.i + 1] == '\0')
					continue;
			}
			sei_la(terminal);
			if(terminal->vars.i > 0)
				terminal->vars.j = terminal->vars.i;
			terminal->vars.new_index = ft_should_expand(terminal->commands->args[i], &terminal->vars.i, terminal);
			printf("new_index: %s\n", terminal->vars.new_index);
			if (!terminal->vars.new_index)
				ft_protection_free(terminal, terminal->vars.new_index);
			sei_la_xx(terminal);
			// if (ft_strncmp(terminal->commands->args[i][0], terminal->vars.var_key, ft_strlen(terminal->commands->args[i][0])))
		}
		printf("teste: %s\n", terminal->vars.var_key);
		break ;
	}	
}
