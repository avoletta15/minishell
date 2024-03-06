/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:45:08 by arabelo-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/06 01:01:54 by arabelo-         ###   ########.fr       */
=======
/*   Updated: 2024/03/05 11:12:03 by mariaavolet      ###   ########.fr       */
>>>>>>> expansion
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function checks if the given parameter is
/// only composed by digits, returns true if it's, else false.
/// @param str 
/// @return 
bool	check_numeric_arg(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/// @brief This function exits the current process.
/// @param terminal 
/// @param args 
void	mini_exit(t_terminal *terminal, char **args)
{
	unsigned char	exit_code;

	if (*args)
		exit_code = ft_atoi(*args);
	else
		exit_code = 0;
	if (!check_numeric_arg(*args))
	{
		exit_non_numeric_arg(*args);
		terminal->exit_status = BAD_SYNTAX;
		exit(BAD_SYNTAX);
	}
	if (size_of_array(args) > 1)
	{
		exit_wrong_args_num();
		terminal->exit_status = FAILURE;
		return ;
	}
	free_terminal(terminal);
	exit(exit_code);
}
