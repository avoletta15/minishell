/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:53:47 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/13 11:10:11 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function checks if the given command is a builtin
/// and returns its corresponding enum value, else zero.
/// @param cmd 
/// @return `t_builtin_types(ENUM)`
t_builtin_types	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(ECHO, cmd, ft_strlen(ECHO) + 1))
		return (ECHO_ID);
	if (!ft_strncmp(CD, cmd, ft_strlen(CD) + 1))
		return (CD_ID);
	if (!ft_strncmp(PWD, cmd, ft_strlen(PWD) + 1))
		return (PWD_ID);
	if (!ft_strncmp(EXPORT, cmd, ft_strlen(EXPORT) + 1))
		return (EXPORT_ID);
	if (!ft_strncmp(UNSET, cmd, ft_strlen(UNSET) + 1))
		return (UNSET_ID);
	if (!ft_strncmp(ENV, cmd, ft_strlen(ENV) + 1))
		return (ENV_ID);
	if (!ft_strncmp(EXIT, cmd, ft_strlen(EXIT) + 1))
		return (EXIT_ID);
	return (0);
}

/// @brief This function checks if there's only one command
/// and is a builtin.
/// @param cmd 
/// @return `bool(true or false)`
bool	is_a_single_builtin(t_command *cmd)
{
	return (!cmd->next && is_builtin(*(cmd->args)));
}

/// @brief This function joins the variable key if its value
/// exists, else duplicates the key and returns it.
/// On error returns NULL, else the address of the duplicated
/// or joined variable.
/// @param env 
/// @return char * or NULL
char	*var_construction(t_env *env)
{
	char	*tmp;
	char	*str;

	if (!env->value)
	{
		tmp = ft_strdup(env->key);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, env->value);
	free(tmp);
	if (!str)
		return (NULL);
	return (str);
}

/// @brief This function builds an array with the environment variables.
/// @param  
/// @return char ** or NULL
char	**convert_env_list_to_array(void)
{
	t_env	*env;
	size_t	env_len;
	char	**array;
	char	*str;

	env = env_api()->env_head;
	env_len = 0;
	array = (char **)ft_calloc(env_api()->len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	while (env)
	{
		str = var_construction(env);
		if (!str)
		{
			free_array(array);
			return (NULL);
		}
		array[env_len++] = str;
		env = env->next;
	}
	return (array);
}

/// @brief This function checks if the given `in (fd)` is not
/// not the `stdin (0)` and closes it, else does nothing, does
/// the same to `out (fd)`, however checks if it's not the `stdout`.
/// @param in 
/// @param out 
void	close_fds(int in, int out)
{
	if (in != STDIN_FILENO && in != -1)
		close(in);
	if (out != STDOUT_FILENO && out != -1)
		close(out);
}
