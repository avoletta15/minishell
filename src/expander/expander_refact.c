/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_refact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:44:44 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/11 20:00:14 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	composed_variable(t_terminal *terminal, int *i)
{
	char	**split;
	char	**new;
	int		j;
	int		n;

	j = 0;
	n = -1;
	new = NULL;

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

char	**more_elemments_array(t_terminal *terminal, int *i)
{
	char		**new;
	size_t		j;
	int			n;

	j = 0;
	n = 0;
	new = (char **)ft_calloc(size_of_array(terminal->commands->args), sizeof(char *));
	if(!new)
		return (NULL);
	while(j < size_of_array(terminal->commands->args))
	{
		if(!ft_strlen(terminal->vars.key) && j == (size_t)*i)
			j++;
		new[n] = terminal->commands->args[j];
		j++;
		n++;
	}
	*i -= 1;
	terminal->commands->args = new;
	return(new);
}

char	*remove_quotes(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)ft_calloc(ft_strlen(old) - 1, sizeof(char *));
	while(old && old[i])
	{
		if(old[i] == SINGLE_QUOTE || old[i] == DOUBLE_QUOTE)
			i++;
		if(old[i] != SINGLE_QUOTE && old[i] != DOUBLE_QUOTE && old[i])
		{
			new[j] = old[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	return(new);
}


void	ft_replacement(t_terminal *terminal, char *flag, int *i)
{
	(void)flag;
	if (!ft_strlen(terminal->vars.key))
	{
		if(size_of_array(terminal->commands->args) <= 1)
		{
			free(terminal->commands->args[0]);
			terminal->commands->args[0] = NULL;
			terminal->commands->cmd_path = NULL;
		}
		else
			more_elemments_array(terminal, i);
	}
	else if(ft_strchr(terminal->vars.key, ' ') && terminal->vars.quoted == false)
		composed_variable(terminal, i);
	else
	{	
		if (terminal->vars.key[0] == SINGLE_QUOTE || terminal->vars.key[0] == DOUBLE_QUOTE)
			terminal->vars.key = ft_substr(remove_quotes(terminal->vars.key), 0, ft_strlen(remove_quotes(terminal->vars.key)));
		terminal->commands->args[*i] = ft_substr(terminal->vars.key, 0, ft_strlen(terminal->vars.key));
		terminal->vars.quoted = false;
	}
}
