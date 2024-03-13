/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:41:33 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/12 21:51:58 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function will start the process of checking if our argumments 
/// have to be expanded or not. If so, organizes into a new string and passes
/// to the next function (ft_replacement).
/// @param terminal 
/// @param flag 
/// @param i 
void	ft_checking_expansion(t_terminal *terminal, char *flag, int i)
{
	while (terminal->commands->args[i] && \
		terminal->commands->args[i][terminal->vars.i])
	{
		if (ft_checking_quotes(terminal->commands->args[i], flag,
				&terminal->vars.i, terminal) == SINGLE_QUOTE)
		{
			terminal->vars.key = ft_substr(terminal->commands->args[i],
					terminal->vars.j, terminal->vars.i);
			if (!terminal->vars.key)
				ft_protection_free(terminal, terminal->vars.key);
			if (terminal->commands->args[i][terminal->vars.i + 1] == '\0')
				continue ;
		}
		temporary_arg_saving(terminal);
		if (terminal->vars.i > 0)
			terminal->vars.j = terminal->vars.i;
		terminal->vars.new_index = should_expand(terminal->commands->args[i],
				&terminal->vars.i, terminal);
		if (!terminal->vars.new_index)
			ft_protection_free(terminal, terminal->vars.new_index);
		new_expanded_var(terminal);
	}
}

/// @brief In case of <single quoted> arguments this function 
/// moves the index itarator to the end of the string
/// @param str 
/// @param i 
void	single_quote_case(char *str, int *i)
{
	while (str && str[*i] != SINGLE_QUOTE && str[*i] != '\0')
	{
		*i += 1;
		if (str[*i] == SINGLE_QUOTE && str[*i + 1] == SINGLE_QUOTE)
			*i += 2;
		else if (str[*i] == SINGLE_QUOTE && str[*i + 1] != '\0')
			*i += 1;
	}
}

/// @brief This function checks if the token is between
/// single or double qoutes, and activates a flag if
/// the token has to be expanded (double quotes).
/// @param str 
/// @param flag 
/// @param i 
/// @return 
char	ft_checking_quotes(char *str, char *flag, int *i, t_terminal *terminal)
{
	if (str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE)
	{
		if (!*flag)
		{
			*flag = str[*i];
			if (*flag == SINGLE_QUOTE)
				*i += 1;
		}
		else
		{
			*flag = '\0';
			terminal->vars.quoted = true;
		}
	}
	if (*flag == SINGLE_QUOTE)
		single_quote_case(str, i);
	return (*flag);
}

/// @brief This function searchs for chars that are
/// not allowed to form variables' names.
/// @param c 
/// @param i 
/// @return 
bool	ft_forbidden_expansion(char c, int i)
{
	if ((ft_isalpha(c) || c == '_') && i == 1)
		return (false);
	else if ((ft_isalnum(c) || c == '_') && i > 1)
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
		if ((str[i] == '?' && i == 1) || \
			ft_forbidden_expansion(str[i], i) == true)
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
