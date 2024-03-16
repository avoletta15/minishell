/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:34:12 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/16 14:20:26 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(char *str, size_t i)
{
	size_t	start;
	
	start = i;
	if (!ft_isalpha(str[i]) && (str[i] != '_' && str[i] != '?'))
		return (-1);
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - start);
}

char	*ft_strrep(char *str, size_t from, size_t len, char *add)
{
	size_t	base_len;
	size_t	new_len;
	char	*new;
	
	base_len = ft_strlen(str);
	new_len = base_len - len + ft_strlen(add);
	new = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (!new)
		return (str);
	ft_strlcpy(new, str, from + 1);
	ft_strlcat(new, add, new_len + 1);
	ft_strlcat(new, str + from + len, new_len + 1);
	return (new);
}

char	*expanded_vars(char *str, size_t *i, char *key)
{
	char	*value;
	char	*temp;

	temp = str;
	if (!ft_strncmp(key, "$", 2))
	{
		*i += 1;
		return (str);
	}
	value = ft_search_variable(key);
	if (!value)
	{
		*i += ft_strlen(key);
		return (str);
	}
	str = ft_strrep(str, *i, ft_strlen(key) + 1, value);
	free(temp);
	if (ft_strlen(value))
		*i += ft_strlen(value) - 1;
	free(value);
	return (str);
}

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

char	*join_the_array(char **array, char *separator)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (array[i])
	{
		len += ft_strlen(array[i]) + ft_strlen(separator);
		i++;
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (array[i])
	{
		ft_strlcat(str, array[i], len + 1);
		ft_strlcat(str, separator, len + 1);
		i++;
	}
	return (str);
}

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
	str = join_the_array(array, "\1");
	if (!str)
		return (array);
	new_array = ft_split(str, PARSER_SEP);
	free(str);
	if (!new_array)
		return (array);
	free_array(array);
	return (new_array);
}

void	command_organization(t_command *command)
{
	while (command)
	{
		command->args = run_the_array(command->args);
		// command_redirects_organization(command->redirections);
		command = command->next;
	}
}

// void	command_redirects_organization(t_redirect *redir)
// {
// 	while (redir)
// 	{
// 		redir->content = ;
// 		redir = redir
// 	}
// }

