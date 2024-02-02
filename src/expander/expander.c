/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:40:19 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/02/02 12:03:12 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function searchs for chars that are
/// not allowed to form variables' names.
/// @param c 
/// @param i 
/// @return 
bool	ft_forbidden_expansion(char c, int i)
{
	if ((ft_isalpha(c) || c == '_') && i == 1)
		return (false);
	else if (ft_isalnum(c) || c == '_')
		return (false);
	return (true);
}

/// @brief This function checks if the variable after the $
/// is formed by valide chars.
/// @param str 
/// @return 
char	*variable_alias(char *str)
{
	char	*expand_var;
	int		i;

	i = 0;
	while (str && str[++i])
	{
		if ((str[i] == '?' && i == 1)
			|| ft_forbidden_expansion(str[i], i) == true)
			break ;
	}
	if (i == 1 && str[i - 1] == '$' && str[i] != '?')
		expand_var = ft_strdup("$");
	else if (i == 1 && str[i])
		expand_var = ft_substr(str, 1, i);
	else
		expand_var = ft_substr(str, 1, (i - 1));
	return (expand_var);
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
	while (env->next)
	{
		if (!ft_strncmp(var, env->info, ft_strlen(var)))
			break ;
		env = env->next;
	}
	if (!env->next)
		return (ft_strdup(""));
	return (ft_strdup(env->info + (ft_strlen(var) + 1)));
}

/// @brief This funtions protects in case of a NULL string
/// is returned.
/// (Build outside the orignal scope because of Norminette requirements).
/// @param terminal 
/// @param expand_var 
void	sei_la(t_terminal *terminal, char *expand_var)
{
	free(expand_var);
	free(terminal->prompt);
	malloc_error();
	exit(EXIT_FAILURE);
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

	if (str[*i] != '$')
	{
		expand_var = ft_substr(str, *i, 1);
		*i += 1;
		return (expand_var);
	}
	expand_var = variable_alias(&str[*i]);
	printf("<< %s >>\n", expand_var);
	if (ft_strncmp(expand_var, "$", ft_strlen("$")))
	{
		*i += ft_strlen(expand_var) + 1;
		expand_var = ft_search_variable(expand_var, terminal);
		if (!expand_var)
			sei_la(terminal, expand_var);
	}
	else if (!ft_strncmp(expand_var, "?", ft_strlen("?")))
		return (ft_itoa(terminal->exit_status));
	else
	{
		*i += ft_strlen("$") + 1;
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

/// @brief This function joins strings and free the original ones.
/// (Build outside the orignal scope because of Norminette requirements).
/// @param test 
/// @param i 
/// @param temp 
/// @param terminal 
/// @return 
char	*ft_join_free(char *test, int i, char *temp, t_terminal *terminal)
{
	char	*var_key;

	free(temp);
	temp = test;
	var_key = ft_strjoin(temp, ft_substr(terminal->tokens->token,
		i, ft_strlen(terminal->tokens->token)));
	return (var_key);
}

/// @brief This function will start the process of checking
/// if a token has to be expanded or not.
/// @param terminal 
/// @param flag 
/// @return 
char	*ft_expansion_check(t_terminal *terminal, char flag)
{

	terminal->vars.i = 0;
	terminal->vars.j = 0;
	terminal->vars.var_key = ft_strdup(terminal->tokens->token);
	terminal->vars.new_index = 0;
	terminal->vars.key = 0;
	while (terminal->tokens && terminal->tokens->token[terminal->vars.i])
	{
		if (ft_checking_quotes(terminal->tokens->token, flag, &terminal->vars.i) == SINGLE_QUOTE)
			terminal->vars.key = ft_substr(terminal->tokens->token, terminal->vars.j, terminal->vars.i);
		if (!terminal->vars.new_index)
			terminal->vars.temp = ft_substr(terminal->vars.var_key, 0, terminal->vars.i);
		else
			terminal->vars.temp = ft_substr(terminal->vars.var_key, 0, ft_strlen(terminal->vars.new_index));
		if(terminal->vars.i > 0)
			terminal->vars.j = terminal->vars.i;
		terminal->vars.new_index = ft_should_expand(terminal->tokens->token, &terminal->vars.i, terminal);
		if(!terminal->vars.key)
			terminal->vars.key = ft_strjoin(terminal->vars.temp, terminal->vars.new_index);
		else
			terminal->vars.key = ft_strjoin(terminal->vars.key, terminal->vars.new_index);
	}
	return (terminal->vars.key);
}
