/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:38:29 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/17 16:02:41 by marioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function will join all the strings
/// of the array into one bigger strin, using the 
/// separator between them. 
/// @param array 
/// @param separator 
/// @return 
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

/// @brief This function rpmes the part of the string to be
/// replaced by the new expanded varibale.
/// @param str 
/// @param from 
/// @param from 
/// @param add 
/// @return 
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

/// @brief This function will rmeove the invalide quotes
/// from the string of arguments.
/// @param old 
/// @return 
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

/// @brief This function counts how many invalide
/// qoutes there are to be removed.
/// @param str 
/// @return 
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
