/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:46:57 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/02/02 11:59:30 by arabelo-         ###   ########.fr       */
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
}

/// @brief Create a new node structure and sets
/// values for its variables
/// @param env_path 
/// @return 
t_env	*new_node(char *env_path)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->info = ft_strdup(env_path);
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

/// @brief Creates the first node, if does not existe yet.
/// Else it adds a new node at the end of the list.
/// @param env_path
/// @param env
/// @return
t_env	*env_structure(char *env_path, t_env *env)
{
	t_env	*new_structure;

	new_structure = NULL;
	if (!env)
	{
		env = new_node(env_path);
		if (!env)
		{
			free_env_list(&env);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_structure = new_node(env_path);
		if (!new_structure)
		{
			free_env_list(&new_structure);
			exit(EXIT_FAILURE);
		}
		add_node_tail(&env, new_structure);
	}
	return (env);
}

/// @brief  Free the contents of the list
/// and the struct itself
/// @param env_structure 
void	free_env_list(t_env **env_structure)
{
	t_env	*tmp;

	tmp = NULL;
	if (!*env_structure)
		return ;
	while (*env_structure)
	{
		tmp = (*env_structure)->next;
		free((*env_structure)->info);
		free(*env_structure);
		*env_structure = tmp;
	}
}
