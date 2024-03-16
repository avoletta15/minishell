/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:44:15 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/16 19:57:38 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function checks it the given string is a valid new line
/// remover, e.g. (-n, -nnnn or -nnnn -nnnn -nnnn).
/// @param option 
/// @return `bool(true or false)`
bool	echo_option_checker(char *option, bool *new_line)
{
	if (*option == '-')
		option++;
	if (*option == '\0')
		return (false);
	while (*option)
	{
		if (*option == 'n')
			*new_line = false;
		else if (*option != 'n')
			return (false);
		option++;
	}
	return (true);
}

/// @brief This function prints the given strings ignoring the `\"new
/// line remover option\"` and printing the following strings, prints
/// a new line if no `\"new line remover option\"` is giving.
/// @param av 
void	echo(char **av, int out, unsigned char *exit_status)
{
	bool	new_line;

	new_line = true;
	while (*av)
	{
		if (echo_option_checker(*av, &new_line))
			av++;
		else
			break ;
	}
	while (*av)
	{
		if (!*(av + 1))
			ft_putstr_fd(*av, out);
		else
		{
			ft_putstr_fd(*av, out);
			ft_putstr_fd(" ", out);
		}
		av++;
	}
	if (new_line)
		ft_putstr_fd("\n", out);
	*exit_status = 0;
}
