/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:46:57 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/05 22:13:38 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Finds the last node of the list
/// @param env 
/// @return 
t_env	*structure_tail_node(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

/// @brief Adds a node at the end of the list
/// @param head 
/// @param new_structure 
void	add_node_tail(t_env **head, t_env *new_structure)
{
	t_env	*last_node;

	if (!head)
		return ;
	if (!*head)
		*head = new_structure;
	else
	{
		last_node = structure_tail_node(*head);
		last_node->next = new_structure;
		new_structure->previous = last_node;
	}
	env_api()->len++;
}

/// @brief Create a new node structure and sets
/// values for its variables
/// @param env_path 
/// @return 
t_env	*new_node(char *env_path)
{
	t_env	*node;
	int	i;

	i = 0;
	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	while (env_path[i] && env_path[i] != '=')
		i++;
	if (env_path[i] == '=')
	{
		node->key = ft_substr(env_path, 0, i++);
		if (!node->key)
			return (free(node), NULL);
		node->value = ft_substr(env_path, i, ft_strlen(&env_path[i]));
		if (!node->value)
			return (free(node->key), free(node->value), NULL);
	}
	else
	{
		node->key = ft_strdup(env_path);
		if (!node->key)
			return (free(node), NULL);
	}
	return(node);
}

/// @brief Creates the first node, if does not existe yet.
/// Else it adds a new node at the end of the list.
/// @param env_path
/// @param env
/// @return
t_env	*env_structure(char *env_path, t_env *env)
{
	t_env	*new_structure;

	if (!env)
	{
		new_structure = new_node(env_path);
		if (!new_structure)
			exit(EXIT_FAILURE);
	}
	else
	{
		new_structure = new_node(env_path);
		if (!new_structure)
		{
			free_env_list(&env);
			exit(EXIT_FAILURE);
		}
	}
	add_node_tail(&env, new_structure);
	return (env);
}

/// @brief  Free the contents of the list
/// and the struct itself
/// @param env_structure 
void	free_env_list(t_env **env_structure)
{
	t_env	*tmp;

	if (!*env_structure)
		return ;
	while (*env_structure)
	{
		tmp = (*env_structure)->next;
		free((*env_structure)->key);
		free((*env_structure)->value);
		free(*env_structure);
		*env_structure = tmp;
	}
}
