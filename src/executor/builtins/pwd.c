/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:32:54 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/03 00:40:36 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function gets the current working directory
/// and displays it, if it fails is displays in the stderr.
/// @param  
void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "pwd: Couldn't get path\n", 23);
		return ;
	}
	printf("%s\n", path);
}
