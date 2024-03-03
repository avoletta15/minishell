/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:00:27 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/01 13:06:59 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function displays an error about the non numeric argument
/// at the exit builtin.
/// @param str 
void	exit_non_numeric_arg(char *str)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, ": exit: ", 8);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
}

/// @brief This function displays an error about the excessive
/// number of arguments at the exit builtin.
/// @param  
void	exit_wrong_args_num(void)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, ": exit: ", 8);
	write(2, ": excessive number of arguments\n", 32);
}

/// @brief This function displays an error about invalid identifier
/// at the export builtin.
/// @param str 
bool	export_invalid_identifier(char *str)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, INVALID_EXPORT_ERROR1, ft_strlen(INVALID_EXPORT_ERROR1));
	write(2, str, ft_strlen(str));
	write(2, INVALID_EXPORT_ERROR2, ft_strlen(INVALID_EXPORT_ERROR2));
	return (false);
}
