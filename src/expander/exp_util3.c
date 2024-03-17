/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_util3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:41:33 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/17 16:03:43 by marioliv         ###   ########.fr       */
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

/// @brief This function searchs for the variable on
/// the env and returns its correspondent.
/// @param var 
/// @param terminal 
/// @return 
char	*ft_search_variable(char *var)
{
	t_env	*env;

	env = env_api()->env_head;
	if (env)
		env = getvar(var);
	if (!env || (env->key && (!env->value || !ft_strncmp(env->value, "", 
					ft_strlen(env->value)))))
		return (ft_strdup(""));
	return (ft_strdup(env->value));
}

/// @brief TThis function gets the lengh of the key to
/// be searched on the evironment
/// @param str 
/// @param i 
/// @return 
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

/// @brief This function receives the velue of the expanded
/// key and calls the ft_strrep() to replace the value where
/// key used to stand inside the argument.
/// @param str 
/// @param i 
/// @param key 
/// @return 
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
