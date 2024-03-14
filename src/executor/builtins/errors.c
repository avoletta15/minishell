/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:05:20 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/13 20:05:42 by arabelo-         ###   ########.fr       */
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

/// @brief This function displays an error message explaining
/// that was not possible to update the value of the given variable.
/// @param str 
void	export_update_value_error(char *str)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, ": export: could not update the value of `", 41);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
}

/// @brief This functionn displays an error message explaining that
/// there's an unclosed quotes at setting a variable.
/// @param str 
void	export_unclosed_quotes(char *str)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, ": export: unclosed quotes at: `", 31);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
}

/// @brief This function displays an error message about the 
/// amount of given parameters to the env builtin.
/// @param  
void	env_args_count_error(unsigned char *exit_status)
{
	write(2, "env: too many arguments\n", 24);
	*exit_status = BAD_SYNTAX;
}
