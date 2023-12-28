/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:28:55 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/28 19:39:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_char_valid(char c, char *base)
{
	while (*base)
	{
		if (c == *base)
			return (1);
		base++;
	}
	return (0);
}

int	get_base_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	if (ft_strlen(base) <= 1 || !ft_check_base(base))
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str && ft_is_char_valid(*str, base))
		res = res * ft_strlen(base) + get_base_index(*str++, base);
	return (sign * res);
}
