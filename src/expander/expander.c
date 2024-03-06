/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:40:19 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/06 13:35:28 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/// @brief This function searchs for the variable on
/// the env and returns its correspondent.
/// @param var 
/// @param terminal 
/// @return 
char	*ft_search_variable(char *var, t_terminal *terminal)
{
	t_env	*env;
	env = terminal->env;
	if(env)
		env = getvar(var);
	if (!env || (env->key && !ft_strncmp(env->value, "", ft_strlen(env->value))))
		return(ft_strdup(""));
	return (ft_strdup(env->value));
}


/// @brief This function starts the process of checking if
/// the variable is allowed and also calls the function to
/// search the vaiable on the env.
/// @param str 
/// @param i 
/// @param terminal 
/// @return 
char	*ft_should_expand(char *str, int *i, t_terminal *terminal)
{
	char	*expand_var;
	if(str[*i] != '$')
	{
		expand_var = ft_substr(str, *i, 1);
		if (!expand_var)
			ft_protection_free(terminal, expand_var);
		*i += 1;
		return (expand_var);
	}
	expand_var = variable_alias(&str[*i]);
	if (!expand_var)
		ft_protection_free(terminal, expand_var);
	if (ft_strncmp(expand_var, "$", ft_strlen("$")))
	{
		*i += ft_strlen(expand_var) + 1;
		expand_var = ft_search_variable(expand_var, terminal);
		if (!expand_var)
			ft_protection_free(terminal, expand_var);
	}
	else if (!ft_strncmp(expand_var, "?", ft_strlen("?")))
		return (ft_itoa(terminal->exit_status));
	else
	{
		*i += 1;
		return (ft_strdup("$"));
	}
	return (expand_var);
}

/// @brief This function checks if the token is between
/// single or double qoutes, and activates a flag if
/// the token has to be expanded (double quotes).
/// @param str 
/// @param flag 
/// @param i 
/// @return 
char	ft_checking_quotes(char *str, char flag, int *i)
{
	if (str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE)
	{
		if (!flag)
			flag = str[*i];
		else
			flag = '\0';
	}
	if (flag == SINGLE_QUOTE)
	{
		while (str && str[*i] != SINGLE_QUOTE)
			*i += 1;
	}
	return(flag);
}

/// @brief  Auxiliar function to ft_expansion_check().
/// (Build outside the orignal scope because of Norminette requirements).
/// @param terminal 
void	ft_init_vars(t_terminal *terminal)
{
	terminal->vars.len = 0;
	// terminal->vars.i = 0;
	terminal->vars.j = 0;
	terminal->vars.new_index = 0;
	terminal->vars.key = 0;
	terminal->vars.var_key = ft_strdup(terminal->commands->args[0]);
	if (!terminal->vars.var_key)
		ft_protection_free(terminal, terminal->vars.var_key);
	while(terminal->commands->args[terminal->vars.len] != NULL)
		++terminal->vars.len;
}

/// @brief Auxiliar function to ft_expansion_check().
/// (Build outside the orignal scope because of Norminette requirements).
/// @param terminal 
void	sei_la(t_terminal *terminal)
{
	if (!terminal->vars.new_index)
	{
		terminal->vars.temp = ft_substr(terminal->vars.var_key, 0, terminal->vars.i);
		if (!terminal->vars.temp)
			ft_protection_free(terminal, terminal->vars.temp);
	}
	else
	{
		terminal->vars.temp = ft_substr(terminal->vars.var_key, 0, ft_strlen(terminal->vars.new_index));
		if (!terminal->vars.temp)
			ft_protection_free(terminal, terminal->vars.temp);
	}
}

/// @brief Auxiliar function to ft_expansion_check().
/// (Build outside the orignal scope because of Norminette requirements).
/// @param terminal 
void	sei_la_xx(t_terminal *terminal)
{
	if(!terminal->vars.key)
	{
		terminal->vars.key = ft_strjoin(terminal->vars.temp, terminal->vars.new_index);
		if (!terminal->vars.var_key)
			ft_protection_free(terminal, terminal->vars.var_key);
	}
	else
	{
		terminal->vars.key = ft_strjoin(terminal->vars.key, terminal->vars.new_index);
		if (!terminal->vars.var_key)
			ft_protection_free(terminal, terminal->vars.var_key);
	}
}

/// @brief This function will start the process of checking
/// if a token has to be expanded or not.
/// @param terminal 
/// @param flag 
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
		while(terminal->commands->args[i] && terminal->commands->args[i][terminal->vars.i])
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
		ft_repelacement(terminal, &i);
		if(terminal->commands->cmd_path == NULL)
			break ;
		if (terminal->commands->args[i + 1] == NULL)
		{
			i = -1;
			terminal->commands = terminal->commands->next;
		}
	}
	terminal->commands = save;
}


/// @brief This function will start the process of checking
/// if a token has to be expanded or not.
/// @param terminal 
/// @param flag 
/// @return 
/* char	*ft_expansion_check(t_terminal *terminal, char flag)
{
	ft_init_vars(terminal);
	while (terminal->tokens && terminal->tokens->token[terminal->vars.i])
	{
		if (ft_checking_quotes(terminal->tokens->token, flag, &terminal->vars.i) == SINGLE_QUOTE)
		{
			terminal->vars.key = ft_substr(terminal->tokens->token, terminal->vars.j, terminal->vars.i);
			if (!terminal->vars.var_key)
				ft_protection_free(terminal, terminal->vars.var_key);
		}
		sei_la(terminal);
		if(terminal->vars.i > 0)
			terminal->vars.j = terminal->vars.i;
		terminal->vars.new_index = ft_should_expand(terminal->tokens->token, &terminal->vars.i, terminal);
		if (!terminal->vars.new_index)
			ft_protection_free(terminal, terminal->vars.new_index);
		sei_la_xx(terminal);
	}
	return (terminal->vars.key);
} */
