/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:06:09 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/03 00:53:13 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function changes the current working directory to
/// the given directory's path. In case of error it displays an
/// error message in the stderr.
/// @param dir_path 
void	cd(char **dir_path)
{
	int		res;
	char	*err;

	if (ft_str_count(dir_path) > 1)
	{
		write(2, "cd: Excessive number of arguments\n", 34);
		return ;
	}
	/// Verify if the command is just cd search for the $HOME environment variable
	/// and if it exits expand and change to this directory, otherwise displays and
	/// error message that this variable is not defined.
	res = chdir(*dir_path);
	if (res == -1)
	{
		write(2, "minishell: ", 11);
		write(2, "cd: ", 4);
		write(2, *dir_path, ft_strlen(*dir_path));
		write(2, ": ", 2);
		err = strerror(errno);
		if (err)
			write(2, err, ft_strlen(err));
		write(2, "\n", 1);
	}
}
