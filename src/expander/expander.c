/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:34:12 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/16 13:31:02 by mariaavolet      ###   ########.fr       */
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

char	*join_the_array(char **array, char *sep)
{
	size_t	i;
	char	*new_str;
	char	*str_joined;
	char	*temp;

	i = 0;
	str_joined = NULL;
	while (array && array[i])
	{
		new_str = ft_strjoin(array[i], sep);
		if (!new_str)
		{
			free(str_joined);
			str_joined = NULL;
			return (NULL);
		}
		if(!str_joined)
			str_joined = new_str;
		else
		{
			temp = str_joined;
			str_joined = ft_strjoin(str_joined, new_str);
			free(temp);
			temp = NULL;
		}
		i++;
		printf("============================================================\n");
		printf("%zu: \n", i);
		printf("new_str: %s\n", new_str);
		printf("temp: %s\n", temp);
		printf("str_joined: %s\n", str_joined);
		printf("============================================================\n");
	}
	free(new_str);
	return(str_joined);
}


char	**run_the_array(char **array)
{
	int				i;
	char			*str;
	t_quotes_system	quotes_sys;

	i = 0;
	while (array && array[i])
	{
		init_quotes_system(&quotes_sys);
		array[i] = expand_str(array[i], &quotes_sys, false);
		i++;
	}
	str = join_the_array(array, "\1");
	free_array(array);
	array = ft_split(str, '\1');
	return (array);
}

void	command_organization(t_command *command)
{
	// char	**array;

	while (command)
	{
		// array = command->args;
		command->args = run_the_array(command->args);
		command = command->next;
	}
}
