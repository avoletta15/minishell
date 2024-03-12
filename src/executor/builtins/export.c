/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:16:12 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/12 08:07:45 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function displays all the environment variables.
/// @param  
void	visualize_export(int out, unsigned char *exit_status)
{
	t_env	*curr;

	curr = env_api()->env_head;
	while (curr)
	{
		if (curr->value)
		{
			ft_putstr_fd("declare -x ", out);
			ft_putstr_fd(curr->key, out);
			ft_putstr_fd("=\"", out);
			ft_putstr_fd(curr->value, out);
			ft_putstr_fd("\"\n", out);
		}
		else
		{
			ft_putstr_fd("declare -x ", out);
			ft_putstr_fd(curr->key, out);
			ft_putstr_fd("\n", out);
		}
		curr = curr->next;
	}
	*exit_status = 0;
}

/// @brief This function checks if the given character is
/// invalid and returns true or false.
/// @param c 
/// @return 
bool	is_var_key_char_valid(char c, int i)
{
	if (i == 0 && (ft_isalpha(c) || c == '_'))
		return (true);
	return (i > 0 && (ft_isalnum(c) || c == '_'));
}

/// @brief This function sets the given variable to the environment
/// variables. If the variable already exists it updates its value.
/// If there's any error it displays it on the stderr.
/// @param str 
void	set_var(char *str)
{
	char	*var;
	t_env	*env;

	var = get_var_key(str);
	if (!var)
	{
		malloc_error();
		return ;
	}
	env = getvar(var);
	free(var);
	if (!env)
	{
		if (!env_api()->new_env_var(str))
			malloc_error();
	}
	else if (!env_api()->update_var(env, str))
		export_update_value_error(env->key);
}

/// @brief This function exports the given arguments to the
/// environment variables and if there's any error displays it
/// on the strerr.
/// @param args 
void	set_export(char **args, unsigned char *exit_status)
{
	bool	error;

	error = false;
	while (args && *args)
	{
		if (!check_new_env(*args))
			error = error || !export_invalid_identifier(*args);
		else
			set_var(*args);
		args++;
	}
	if (error)
		*exit_status = 1;
	else
		*exit_status = 0;
}

/// @brief This function checks if the user only wants to show the
/// environment variables or set any variable.
/// @param args
void	export(char **args, int out, unsigned char *exit_status)
{
	if (!args || !*args)
		visualize_export(out, exit_status);
	else
		set_export(args, exit_status);
}
