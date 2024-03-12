/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:44:52 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/12 22:00:56 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function is called whenever the program detects
/// an argument that is precieved by a $
/// @param str 
/// @param i 
/// @param terminal 
/// @param expand_var 
/// @return 
char	*should_not_expand(char *str, int *i, t_terminal *terminal, 
			char *expand_var)
{
	expand_var = ft_substr(str, *i, 1);
	if (!expand_var)
		ft_protection_free(terminal, expand_var);
	*i += 1;
	return (expand_var);
}

/// @brief When the variable calls the exit status ($?)
/// this fucntion returns the exit status to be injected
/// on the array of arguments.
/// @param terminal 
/// @param i 
/// @return 
char	*exit_status_expansion(t_terminal *terminal, int *i)
{
	*i += 2;
	return (ft_itoa(terminal->exit_status));
}

/// @brief This function starts the process of checking if
/// the variable is allowed and also calls the function to
/// search the vaiable on the env.
/// @param str 
/// @param i 
/// @param terminal 
/// @return 
char	*should_expand(char *str, int *i, t_terminal *terminal)
{
	char	*expand_var;

	expand_var = NULL;
	if (str[*i] != '$')
		return (should_not_expand(str, i, terminal, expand_var));
	expand_var = variable_alias(&str[*i]);
	if (!expand_var)
		ft_protection_free(terminal, expand_var);
	if (!ft_strncmp(expand_var, "?", ft_strlen("?")))
		return (exit_status_expansion(terminal, i));
	else if (ft_strncmp(expand_var, "$", ft_strlen("$")))
	{
		*i += ft_strlen(expand_var) + 1;
		expand_var = ft_search_variable(expand_var, terminal);
		if (!expand_var)
			ft_protection_free(terminal, expand_var);
	}
	else
	{
		*i += 1;
		return (ft_strdup("$"));
	}
	return (expand_var);
}
