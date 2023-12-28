/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:17:21 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/28 19:39:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_counter(char const *s, char c)
{
	size_t	words_counter;

	words_counter = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			words_counter++;
		while (*s != c && *s)
			s++;
	}
	return (words_counter);
}

static void	free_split(char **list, int index)
{
	int	i;

	i = 0;
	while (i < index)
		free(list[i++]);
	free(list);
}

static char	*ft_copy(char const *s, char **list, char c, int index)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	list[index] = ft_substr(s, 0, i);
	if (!list[index])
	{
		free_split(list, index);
		return (NULL);
	}
	return ((char *)s + i);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	list = (char **)malloc(sizeof(*list) * (ft_word_counter(s, c) + 1));
	if (!list)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			s = ft_copy(s, list, c, index);
			if (!s)
				return (NULL);
			index++;
		}
	}
	list[index] = 0;
	return (list);
}
