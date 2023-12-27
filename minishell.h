/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:52:10 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/27 14:27:11 by arabelo-         ###   ########.fr       */
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

# define SINGLE_QUOTE "\'"
# define DOUBLE_QUOTE "\""
# define PIPE "|"
# define INPUT_REDIRECT "<"
# define OUTPUT_REDIRECT ">"
# define HERE_DOC "<<"
# define APPEND ">>"

typedef enum e_token_types {
	SINGLE_QUOTE_ID = 1,
	DOUBLE_QUOTE_ID = 2,
	INPUT_REDIRECT_ID = 3,
	OUTPUT_REDIRECT_ID = 4,
	PIPE_ID = 5,
	HERE_DOC_ID = 6,
	APPEND_ID = 7,
	ARGS_ID = 8,
	INFILE_ID = 9,
	OUTFILE_ID = 10,
}			t_token_types;

typedef struct s_quotes_system
{
	char	*prompt;
	char	**prompt_splitted;
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

typedef struct s_token
{
	int				token_id;
	char			*token;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_program
{
	char			*command_line;
	t_command		*commands;
	t_token			*tokens;
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
char		*second_filter(t_quotes_system *quote);
bool		lexer(t_program *program);
// lexer

// prompt treatment
void		remove_whitespaces(char *dest, char *src, t_quotes_system *quotes);
void		delimit_special_chars(char *dest,
				char *src, t_quotes_system *quote);
void		free_prompt(char **prompt_splitted);
// prompt treatment

// memory
void		free_project(t_quotes_system *quote, void (*call_back)(void));
// memory

// tokenize
int			get_token_id(char *token);
t_token		*create_token(char *token);
void		add_token(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
void		tokenize_prompt(char **prompt_splitted, t_token **tokens);
// tokenize

// utils
int			is_special_chars(char *set);
void		copynstr(char *dest, char *src, size_t len);
void		put_separator(char **dest, char **src, int *pos);
void		print_token(t_token *token);
void		visualize_tokens(t_token *tokens);
// utils

#endif
