/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:32:54 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/01 19:18:28 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function gets the current working directory
/// and displays it, if it fails is displays in the stderr.
/// @param  
void	pwd(int out, unsigned char *exit_status)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "pwd: couldn't get path\n", 23);
		*exit_status = 1;
		return ;
	}
	ft_putendl_fd(path, out);
	free(path);
}
