/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:45:08 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/17 17:03:50 by marioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function checks if the given parameter is
/// only composed by digits, returns true if it's, else false.
/// @param str 
/// @return 
bool	check_numeric_arg(char *str)
{
	if (!str)
		return (true);
	if (*str != '+' && *str != '-' && !ft_isdigit(*str))
		return (false);
	str++;
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
		exit_code = terminal->exit_status;
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
	close_cmds_fds(terminal->commands, true);
	free_terminal(terminal);
	exit(exit_code);
}
