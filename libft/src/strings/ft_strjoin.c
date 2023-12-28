/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:36:57 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/28 19:39:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (!ptr)
		return (ptr);
	while (s1_len > i)
		ptr[i++] = *(char *)s1++;
	while (s1_len + s2_len > i)
		ptr[i++] = *(char *)s2++;
	ptr[i] = '\0';
	return (ptr);
}
