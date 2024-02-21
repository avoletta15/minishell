/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:45:08 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/21 19:40:11 by arabelo-         ###   ########.fr       */
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

/// @brief This function deallocates all previous allocated
/// memory to exit the process.
/// @param terminal 
void	exit_process(t_terminal *terminal)
{
	free_args(terminal->args);
	free_commands(terminal);
	free_env_list(&env_api()->env_head);
	free(terminal->prompt);
	free_prompt(terminal->prompt_splitted);
	free_structs(terminal, false, NULL);
}

/// @brief This function exits the current process.
/// @param terminal 
/// @param args 
void	mini_exit(t_terminal *terminal, char **args)
{
	if (!check_numeric_arg(*args))
	{
		exit_non_numeric_arg(*args);
		terminal->exit_status = BAD_SYNTAX;
		exit(BAD_SYNTAX);
	}
	else if (ft_str_count(args) > 1)
	{
		exit_wrong_args_num();
		terminal->exit_status = FAILURE;
		return ;
	}
	exit_process(terminal);
	exit((unsigned char)ft_atoi(*args));
}
