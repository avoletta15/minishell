/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:16:12 by arabelo-          #+#    #+#             */
/*   Updated: 2024/02/20 22:18:15 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function displays all the environment variables.
/// @param  
void	visualize_export(void)
{
	t_env	*curr;

	curr = env_api()->env_head;
	while (curr)
	{
		if (curr->value)
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
		else
			printf("declare -x %s\n", curr->key);
		curr = curr->next;
	}
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
void	set_export(char **args)
{
	t_env	*env;

	while (args && *args)
	{
		if (!check_new_env(*args))
		{
			write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
			write(2, INVALID_EXPORT_ERROR1, ft_strlen(INVALID_EXPORT_ERROR1));
			write(2, *args, ft_strlen(*args));
			write(2, INVALID_EXPORT_ERROR2, ft_strlen(INVALID_EXPORT_ERROR2));
		}
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
}

/// @brief This function checks if the user only wants to show the
/// environment variables or set any variable.
/// @param args
void	export(char **args)
{
	if (!args || !*args)
		visualize_export();
	else
		set_export(args);
}
