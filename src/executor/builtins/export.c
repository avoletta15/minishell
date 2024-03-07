/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:16:12 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/07 18:25:43 by arabelo-         ###   ########.fr       */
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
bool	invalid_char_env(char c)
{
	return (!ft_isalnum(c) && c != '_'
		&& c != '=' && c != DOUBLE_QUOTE && c != SINGLE_QUOTE);
}

/// @brief This function checks if the exported variable and
/// its value are valid. Checks unclosed quotes as well, on error
/// returns false, else true.
/// @param str 
/// @return 
bool	check_new_env(char *str)
{
	char	quote;
	char	*original;

	quote = 0;
	original = str;
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	while ((++str, *str))
	{
		if (invalid_char_env(*str))
			return (false);
		if (!quote && (*str == SINGLE_QUOTE || *str == DOUBLE_QUOTE))
			quote = *str;
		else if (quote == *str)
			quote = 0;
	}
	if (quote)
	{
		export_unclosed_quotes(original);
		return (false);
	}
	return (true);
}

/// @brief This function exports the given arguments to the
/// environment variables and if there's any error displays it
/// on the strerr.
/// @param args 
void	set_export(char **args, unsigned char *exit_status)
{
	t_env	*env;
	bool	error;

	error = false;
	while (args && *args)
	{
		if (!check_new_env(*args))
			error = error || !export_invalid_identifier(*args);
		else
		{
			env = getvar(*args);
			if (!env)
			{
				if (!env_api()->new_env_var(*args))
					malloc_error();
			}
			else if (!env_api()->update_var(env, *args))
				export_update_value_error(env->key);
		}
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
