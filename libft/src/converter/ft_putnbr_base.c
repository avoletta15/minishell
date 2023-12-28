/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:31:22 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/28 19:39:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbase(unsigned long nbr, char *base)
{
	if (nbr > ft_strlen(base) - 1)
	{
		ft_putbase(nbr / ft_strlen(base), base);
		ft_putbase(nbr % ft_strlen(base), base);
	}
	else
		ft_putchar_fd(base[nbr % ft_strlen(base)], 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	if (ft_strlen(base) <= 1 || !ft_check_base(base))
		return ;
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		ft_putbase(-nbr, base);
	}
	else
		ft_putbase(nbr, base);
}
