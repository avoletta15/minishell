/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_refact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:44:44 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/04 11:23:55 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expansion_check_refac(t_terminal *terminal, char flag)
{
	t_command	*save;
	int			i;

	i = -1;
	save = terminal->commands;
	while(terminal->commands && terminal->commands->args && terminal->commands->args[++i])
	{
		ft_init_vars(terminal);
		terminal->vars.i = 0;
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
			if (!terminal->vars.new_index)
				ft_protection_free(terminal, terminal->vars.new_index);
			sei_la_xx(terminal);
		}
		/* if (ft_strncmp(" ", terminal->vars.key, ft_strlen(" "))) 
			refazer o array sem aquela parte
			*/
		if (ft_strncmp(terminal->commands->args[i], terminal->vars.key, ft_strlen(terminal->vars.key)))
			ft_repelacement(terminal, &i);
		if (terminal->commands->args[i + 1] == NULL)
		{
			i = -1;
			terminal->commands = terminal->commands->next;
		}
	}
	terminal->commands = save;
}

void	ft_repelacement(t_terminal *terminal, int *i)
{
	char	**split;
	char	**new;
	int		j;
	int		n;


	j = 0;
	n = -1;
	new = NULL;
	// if (!ft_strncmp(" ", terminal->vars.key, ft_strlen(" ")))
	// 	terminal = ft_cansada(terminal, *i);
	if ((*i - 1 >= 0 && !ft_strncmp(terminal->commands->args[*i - 1], "echo", ft_strlen("echo")))  || !ft_strchr(terminal->vars.key, ' '))
		terminal->commands->args[*i] = ft_substr(terminal->vars.key, 0, ft_strlen(terminal->vars.key));
	else
	{
		split = ft_split(terminal->vars.key, ' ');
		while(split[j] != NULL)
			j++;
		new = (char **)ft_calloc((j + terminal->vars.len + 1), sizeof(char *));
		j = -1;
		while(++j != *i)
			new[j] = terminal->commands->args[j];
		while(split[++n] != NULL)
		{
			new[j] = split[n];
			j++;
		}
		n = *i + 1;
		while(terminal->commands->args[n] != NULL)
		{
			new[j] = terminal->commands->args[n];
			j++;
			n++;
		}
		new[j] = NULL;
		*i += 1;
		terminal->commands->args = new;
	}
}

// t_terminal	*ft_cansada(t_terminal *terminal, int *i)
// {
// 	t_terminal	*new;
// 	int			j;
// 	int			n;

// 	n = -1;
// 	j = 0;
// 	new = (t_terminal *)ft_calloc(1, (sizeof(t_terminal)));
// 	if(!new)
// 		return(NULL);
// 	while (++n != *i)
// 		new->commands->args[n] = terminal->commands->args[n];
// 	j = *i + 1;
// 	while(terminal->commands->args[j] != '\0')
// 	{
// 		new->commands->args[n] = terminal->commands->args[j];
// 		n++;
// 		j++;
// 	}
// 	new->commands->args[n] = '\0';
// 	return (new);
// }