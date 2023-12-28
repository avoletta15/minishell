/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:52:01 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/28 19:39:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// This function searches for a given integer
// in the array, it works halving the array and 
// checking if the integer is greater or smaller
// than the integer found, and moves to one
// of the halves based on the result.
// In order for this function to properly work
// the given array should be in ascending order.
// A wrong len will result either a false result
// or segmentation fault.
int	ft_binary_search(int *array, int searched_int, size_t len)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = len - 1;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (array[mid] == searched_int)
			return (mid);
		else if (array[mid] < searched_int)
			left = mid + 1;
		else if (array[mid] > searched_int)
			right = mid - 1;
	}
	return (-1);
}
