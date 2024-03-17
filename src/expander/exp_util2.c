/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:55:44 by marioliv          #+#    #+#             */
/*   Updated: 2024/03/17 16:03:07 by marioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function receives the value of exit status
//  and calls the ft_strrep() to replace the value where
/// key used to stand inside the argument.
/// @param str 
/// @param quotes_sys 
/// @return 
char	*exit_status_management(char *str, t_quotes_system *quotes_sys)
{
	char	*value;
	char	*temp;

	value = ft_itoa(get_terminal()->exit_status);
	if (!value)
	{
		quotes_sys->i += 1;
		return (str);
	}
	temp = str;
	str = ft_strrep(str, quotes_sys->i, 2, value);
	quotes_sys->i += ft_strlen(value) - 1;
	free(temp);
	free(value);
	return (str);
}

/// @brief This function checks if the argumment needs to be expanded
/// or not. If so, calls expander() to handle it.
/// @param str 
/// @param quotes_sys 
/// @param is_in_here_doc
/// @return 
char	*expand_str(char *str, t_quotes_system *quotes_sys, bool is_in_here_doc)
{
	while (str[quotes_sys->i])
	{
		if (str[quotes_sys->i] == '$' && (quotes_sys->quote != SINGLE_QUOTE
				|| is_in_here_doc))
			str = expander(str, quotes_sys);
		quotes_iterator(quotes_sys, str[quotes_sys->i]);
	}
	return (str);
}

/// @brief This function will call the auxiliar ones, in order
/// to prep the string of arguments to be splited.
/// @param str 
/// @param array 
/// @param quotes_sys 
void	manipulate_str(char **str, char **array, t_quotes_system *quotes_sys)
{
	char	*temp;

	*str = join_the_array(array, "\1");
	if (!*str)
		return ;
	remove_whitespaces(*str, quotes_sys);
	temp = *str;
	*str = remove_quotes(*str);
	init_quotes_system(quotes_sys);
	free(temp);
}
