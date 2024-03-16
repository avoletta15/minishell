/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:34:12 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/16 20:50:12 by arabelo-         ###   ########.fr       */
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

size_t	quotes_count(char *str)
{
	size_t	q;

	q = 0;
	while (str && *str)
	{
		if (*str == SINGLE_QUOTE || *str == DOUBLE_QUOTE)
			q++;
		str++;
	}
	return (q);
}

char	*remove_quotes(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!old)
		return (NULL);
	new = (char *)ft_calloc(ft_strlen(old)
		- quotes_count(old) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	while (old && old[i])
	{
		if (old[i] == SINGLE_QUOTE || old[i] == DOUBLE_QUOTE)
			i++;
		if (old[i] != SINGLE_QUOTE && old[i] != DOUBLE_QUOTE && old[i])
		{
			new[j] = old[i];
			i++;
			j++;
		}
	}
	return (new);
}

void	manipulate_str(char **str, char **array, t_quotes_system *quotes_sys)
{
	char	*temp;

	*str = join_the_array(array, "\1");
	temp = *str;
	*str = remove_quotes(*str);
	init_quotes_system(quotes_sys);
	remove_whitespaces(*str, quotes_sys);
	free(temp);
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

void	generic_expansion(t_terminal *terminal)
{
	t_command *cmd;

	cmd = terminal->commands;
	while (cmd)
	{
		cmd->args = run_the_array(cmd->args);
		run_redirections(cmd->redirections);
		cmd = cmd->next;
	}
	cmd = terminal->commands;
}
