/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:05:20 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/14 10:51:48 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function displays the count error when cd is
/// executed with more than one parameter and returns false.
/// @param  
/// @return 
bool	cd_args_count_error(void)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, CD_ARGS_COUNT_ERROR, ft_strlen(CD_ARGS_COUNT_ERROR));
	return (false);
}

/// @brief This function displays an spefic error on the stderr
/// when the cd builtin fails. It returns always false.
/// @param dir_path 
/// @return 
bool	cd_fail(char *dir_path)
{
	char	*err;

	write(2, "minishell: ", 11);
	write(2, "cd: ", 4);
	write(2, dir_path, ft_strlen(dir_path));
	write(2, ": ", 2);
	err = strerror(errno);
	if (err)
		write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (false);
}
