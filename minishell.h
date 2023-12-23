/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:52:10 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/23 15:54:38 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PARSER_SEP '\1'

# define BAD_SYNTAX_ERROR "Error: Bad syntax\n"
# define MALLOC_ERROR "Error: Malloc failed\n"

typedef enum e_characters_types {
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE = 2,
	INPUT_REDIRECT = 3,
	OUTPUT_REDIRECT = 4,
	HERE_DOC = 5,
	APPEND = 6,
}			t_characters_types;

typedef struct s_quotes_system
{
	char	*prompt;
	char	quote;
	size_t	index;
	size_t	len;
	bool	quote_state;
	bool	changed;
	bool	error;
	bool	was_just_in_quotes;
}				t_quotes_system;

typedef struct s_command
{
	char				*command;
	char				*flags;
	struct s_command	*next_command;
}				t_command;

typedef struct s_program
{
	char			*command_line;
	t_command		*commands;
	t_quotes_system	quotes_system;
}				t_program;

// error
void		bad_syntax_error(void);
void		malloc_error(void);
// error

// init vars
void		init_program(t_program *program);
void		init_quotes_system(t_quotes_system *quotes_system);
// init vars

// lexer
char		*first_filter(t_quotes_system *quote);
// lexer

// prompt treatment
void		remove_whitespaces(char *dest, char *src, t_quotes_system *quotes);
// prompt treatment

// memory
void		free_project(t_quotes_system *quote, void (*call_back)(void));
// memory
#endif
