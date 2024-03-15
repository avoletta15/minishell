/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:44:52 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/15 16:51:14 by mariaavolet      ###   ########.fr       */
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
// char	*should_not_expand(char *str, int *i, t_terminal *terminal,
// 			char *expand_var)
// {
// 	expand_var = ft_substr(str, *i, 1);
// 	if (!expand_var)
// 		ft_protection_free(terminal, expand_var);
// 	*i += 1;
// 	return (expand_var);
// }

/// @brief When the variable calls the exit status ($?)
/// this fucntion returns the exit status to be injected
/// on the array of arguments.
/// @param terminal 
/// @param i 
/// @return 
// char	*exit_status_expansion(t_terminal *terminal, size_t *i)
// {
// 	return (ft_itoa(terminal->exit_status));
// }

/// @brief This function starts the process of checking if
/// the variable is allowed and also calls the function to
/// search the vaiable on the env.
/// @param str 
/// @param i 
/// @param terminal 
/// @return 
// char	*should_expand(char *str, int *i, t_terminal *terminal)
// {
// 	char	*expand_var;
// 	char	*temp;

// 	if (str[*i] != '$')
// 		return (should_not_expand(str, i, terminal, NULL));
// 	expand_var = variable_alias(&str[*i]);
// 	if (!expand_var)
// 		ft_protection_free(terminal, expand_var);
// 	if (!ft_strncmp(expand_var, "?", ft_strlen("?")))
// 		return (exit_status_expansion(terminal, i, expand_var));
// 	else if (ft_strncmp(expand_var, "$", ft_strlen("$")))
// 	{
// 		*i += ft_strlen(expand_var) + 1;
// 		temp = expand_var;
// 		expand_var = ft_search_variable(temp, terminal);
// 		free(temp);
// 		if (!expand_var)
// 			ft_protection_free(terminal, expand_var);
// 	}
// 	else
// 		*i += 1;
// 	return (expand_var);
// }

/// @brief This function call the remove_quotes() function
/// and injects the result on the variable, to be later injected
/// on the array of arguments. On error it frees the terminal,
/// the variable and exit the program.
/// @param terminal 
// void	injecting_removed_quotes(t_terminal *terminal)
// {
// 	char	*temp;
// 	size_t	temp_len;

// 	temp = remove_quotes(terminal->vars.key);
// 	free(terminal->vars.key);
// 	if (!temp)
// 		ft_protection_free(terminal, temp);
// 	temp_len = ft_strlen(temp);
// 	terminal->vars.key = ft_substr(temp, 0, temp_len);
// 	free(temp);
// 	if (!terminal->vars.key)
// 		ft_protection_free(terminal, terminal->vars.key);
// }
