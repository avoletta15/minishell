/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:54:31 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/06 15:17:17 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

char	*gnl_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s == (char)c)
		return (s);
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (!join)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			join[i] = s1[i];
			i++;
		}
	}
	while (*s2)
		join[i++] = *s2++;
	join[i] = '\0';
	free(s1);
	return (join);
}
