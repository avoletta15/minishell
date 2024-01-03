/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:20:27 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/03 16:58:35 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function changes the ownership of the
/// args strings to the command array of strings.
/// @param terminal 
/// @param command 
/// @param counter 
void	fill_command_args(t_terminal *terminal,
		t_command *command, size_t counter)
{
	size_t	i;
	t_args	*curr;

	i = 0;
	curr = terminal->args;
	while (i < counter)
	{
		command->args[i++] = curr->args;
		curr->args = NULL;
		curr = curr->next;
	}
}

/// @brief This function iterates over the tokens from the terminal
/// util it finds a pipe('|') or the end of the list. It accumulates
/// all arguments and redirection it finds. If any memory allocation
/// fails it deallocates all previously allocated memory and exits
/// the process.
/// @param terminal 
/// @param cursor 
void	accumulator(t_terminal *terminal, t_token **cursor)
{
	t_token			*head;
	t_token_types	token_id;

	head = *cursor;
	while (head)
	{
		token_id = get_token_id(head->token);
		if (token_id == PIPE_ID)
			break ;
		else if (token_id == ARGS_ID)
		{
			add_arg(terminal, head);
			head = head->next;
		}
		else
		{
			add_redirect(terminal, head);
			head = head->next->next;
		}
	}
	*cursor = head;
}

/// @brief This function uses the accumulated arguments and redirections
/// to generate a command struct and if any point some allocation fails
/// it deallocates all previously allocated memory and exits the process.
/// @param terminal 
/// @return 
t_command	*create_command(t_terminal *terminal)
{
	t_command	*command;
	size_t		counter;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	counter = count_args(terminal);
	command->args = (char **)ft_calloc(counter + 1, sizeof(char *));
	if (!command->args)
	{
		free(command);
		return (NULL);
	}
	fill_command_args(terminal, command, counter);
	command->redirections = terminal->redirects;
	free_args(terminal->args);
	terminal->args = NULL;
	terminal->redirects = NULL;
	return (command);
}

/// @brief This function appends the given command into the
/// terminal command list.
/// @param terminal 
/// @param command 
void	add_command(t_terminal *terminal, t_command *command)
{
	t_command	*curr;

	if (!terminal->commands)
	{
		terminal->commands = command;
		return ;
	}
	curr = terminal->commands;
	while (curr->next)
		curr = curr->next;
	curr->next = command;
}

/// @brief This function parses all the tokens from the terminal.
/// If at any point any allocation fails it deallocates all
/// previously allocated memory and exits the process.
/// The function returns true if it executes successfully.
/// @param terminal 
/// @return 
bool	parser(t_terminal *terminal)
{
	t_token		*head;
	t_command	*command;

	head = terminal->tokens;
	while (head)
	{
		accumulator(terminal, &head);
		command = create_command(terminal);
		if (!command)
			free_structs(terminal, true, &malloc_error);
		add_command(terminal, command);
		if (head)
			head = head->next;
	}
	free_tokens(terminal->tokens);
	terminal->tokens = NULL;
	return (true);
}
