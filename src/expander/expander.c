/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:34:12 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/17 16:02:07 by marioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This is the main function that will call
/// auxiliar ones according to the type of expansion
/// that must happen.
/// @param str 
/// @param quotes_sys 
/// @return 
char	*expander(char *str, t_quotes_system *quotes_sys)
{
	char	*key;
	char	*new_str;

	key = variable_alias(&str[quotes_sys->i]);
	if (!key)
	{
		quotes_sys->i += get_var_len(str, quotes_sys->i + 1);
		return (str);
	}
	else if (!ft_strncmp(key, "?", 2))
	{
		free(key);
		return (exit_status_management(str, quotes_sys));
	}
	new_str = expanded_vars(str, &quotes_sys->i, key);
	free(key);
	return (new_str);
}

/// @brief This main function runs the array of arguments,
/// calling the auxiliar ones to make the arguments ready for
/// the executor. 
/// @param array 
/// @return 
char	**run_the_array(char **array)
{
	int				i;
	char			*str;
	char			**new_array;
	t_quotes_system	quotes_sys;

	i = 0;
	while (array && array[i])
	{
		init_quotes_system(&quotes_sys);
		array[i] = expand_str(array[i], &quotes_sys, false);
		i++;
	}
	manipulate_str(&str, array, &quotes_sys);
	if (!str)
		return (array);
	new_array = ft_split(str, PARSER_SEP);
	free(str);
	if (!new_array)
		return (array);
	free_array(array);
	return (new_array);
}

/// @brief This function will check, according to the redirection
/// type how it should be handled, and call the auxiliar fuctions
/// according to it.
/// @param redir 
void	run_redirections(t_redirect *redir)
{
	t_quotes_system	quotes_sys;
	char			*temp;

	while (redir)
	{
		init_quotes_system(&quotes_sys);
		if (!ft_strlen(redir->content) || redir->toked_id == HERE_DOC_ID)
		{
			redir = redir->next;
			continue ;
		}
		redir->content = expand_str(redir->content, &quotes_sys, false);
		temp = remove_quotes(redir->content);
		free(redir->content);
		redir->content = temp;
		if ((!quotes_sys.was_quoted && ft_strchr(redir->content, ' '))
			|| !ft_strlen(redir->content))
			redir->invalid_expansion = true;
		redir = redir->next;
	}
}

/// @brief This function is used to call the other main
/// functions that deals with each type of expansion. 
/// @param terminal 
void	generic_expansion(t_terminal *terminal)
{
	t_command	*cmd;

	cmd = terminal->commands;
	while (cmd)
	{
		cmd->args = run_the_array(cmd->args);
		run_redirections(cmd->redirections);
		cmd = cmd->next;
	}
	cmd = terminal->commands;
}
