/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:38:29 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/12 22:04:11 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Auxiliar function to ft_expansion_check().
/// (Build outside the orignal scope because of Norminette requirements).
/// @param terminal 
void	temporary_arg_saving(t_terminal *terminal)
{
	if (!terminal->vars.new_index)
	{
		terminal->vars.temp = ft_substr(terminal->vars.var_key, 
				0, terminal->vars.i);
		if (!terminal->vars.temp)
			ft_protection_free(terminal, terminal->vars.temp);
	}
	else
	{
		terminal->vars.temp = ft_substr(terminal->vars.var_key,
				0, ft_strlen(terminal->vars.new_index));
		if (!terminal->vars.temp)
			ft_protection_free(terminal, terminal->vars.temp);
	}
}

/// @brief Replace the string with the expanded version of the argument
/// @param terminal 
void	new_expanded_var(t_terminal *terminal)
{
	if (!terminal->vars.key)
	{
		terminal->vars.key = ft_strjoin(terminal->vars.temp, 
				terminal->vars.new_index);
		if (!terminal->vars.var_key)
			ft_protection_free(terminal, terminal->vars.var_key);
	}
	else
	{
		terminal->vars.key = ft_strjoin(terminal->vars.key, 
				terminal->vars.new_index);
		if (!terminal->vars.var_key)
			ft_protection_free(terminal, terminal->vars.var_key);
	}
	free(terminal->vars.new_index);
	free(terminal->vars.temp);
	terminal->vars.temp = NULL;
	terminal->vars.new_index = NULL;
}

/// @brief This function searchs for the variable on
/// the env and returns its correspondent.
/// @param var 
/// @param terminal 
/// @return 
char	*ft_search_variable(char *var, t_terminal *terminal)
{
	t_env	*env;

	env = terminal->env;
	if (env)
		env = getvar(var);
	if (!env || (env->key && !ft_strncmp(env->value, "", 
				ft_strlen(env->value))))
		return (ft_strdup(""));
	return (ft_strdup(env->value));
}

/// @brief  Auxiliar function to ft_expansion_check().
/// (Build outside the orignal scope because of Norminette requirements).
/// @param terminal 
void	ft_init_vars(t_terminal *terminal, int arg)
{
	terminal->vars.quoted = false;
	terminal->vars.len = 0;
	terminal->vars.j = 0;
	terminal->vars.new_index = 0;
	terminal->vars.key = 0;
	terminal->vars.var_key = ft_strdup(terminal->commands->args[arg]);
	if (!terminal->vars.var_key)
		ft_protection_free(terminal, terminal->vars.var_key);
	while (terminal->commands->args[terminal->vars.len] != NULL)
		++terminal->vars.len;
}

/// @brief This function will start the process of checking
/// if a token has to be expanded or not.
/// @param terminal 
/// @param flag 
void	ft_expansion(t_terminal *terminal, char flag)
{
	t_command	*save;
	int			i;

	i = -1;
	save = terminal->commands;
	while (terminal->commands && terminal->commands->args
		&& terminal->commands->args[++i])
	{
		ft_init_vars(terminal, i);
		terminal->vars.i = 0;
		ft_checking_expansion(terminal, &flag, i);
		ft_replacement(terminal, &flag, &i);
		if (terminal->commands->cmd_path == NULL)
			break ;
		if (terminal->commands->args[i + 1] == NULL)
		{
			i = -1;
			terminal->commands = terminal->commands->next;
		}
	}
	terminal->commands = save;
}
