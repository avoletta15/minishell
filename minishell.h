/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:52:10 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/11 11:40:00 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PARSER_SEP '\1'

# define UNCLOSED_QUOTE_ERROR "Error: unclosed quote\n"
# define MALLOC_ERROR "Error: Malloc failed\n"
# define BAD_SYNTAX_ERROR1 "minishell: bad syntax "
# define BAD_SYNTAX_ERROR2 "error near to the unexpected token "
# define NEW_LINE "newline"

# define PIPE "|"
# define INPUT_REDIRECT "<"
# define OUTPUT_REDIRECT ">"
# define HERE_DOC "<<"
# define APPEND ">>"
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

typedef enum e_token_types {
	INPUT_REDIRECT_ID = 1,
	OUTPUT_REDIRECT_ID,
	HERE_DOC_ID,
	APPEND_ID,
	PIPE_ID,
	BUILT_IN_ID,
	ARGS_ID,
}			t_token_types;

typedef struct s_quotes_system
{
	char	*prompt;
	char	**prompt_splitted;
	char	quote;
	bool	quote_state;
}				t_quotes_system;

typedef struct s_command
{
	char				*command;
	char				*flags;
	struct s_command	*next_command;
}				t_command;

typedef struct s_token
{
	t_token_types	token_id;
	char			*token;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*info;
	struct s_env	*previous;
	struct s_env	*next;
}				t_env;

typedef struct s_program
{
	char			*prompt;
	char			**prompt_splitted;
	t_command		*commands;
	t_token			*tokens;
	int				exit_status;
	t_quotes_system	quotes_system;
}				t_terminal;

// error
void		unclosed_quote_error(void);
void		malloc_error(void);
void		bad_syntax_error(char *str);
void		invalid_token_error(t_terminal *terminal, char *str);
// error

// init vars
void		reset_terminal(t_terminal *terminal, bool reset_all);
void		init_terminal(t_terminal *terminal, bool reset_all);
void		init_quotes_system(t_quotes_system *quotes_system);
// init vars

// lexer
bool		first_filter(t_terminal *terminal);
bool		second_filter(t_terminal *terminal);
bool		third_filter(t_terminal *terminal);
bool		lexer(t_terminal *terminal);
// lexer

// prompt treatment
void		remove_whitespaces(char *dest, char *src, t_quotes_system *quotes);
void		delimit_special_chars(char *dest,
				char *src, t_quotes_system *quote);
void		free_prompt(char **prompt_splitted);
// prompt treatment

// memory
void		free_project(t_terminal *terminal, void (*call_back)(void));
// memory

// tokenize
int			get_token_id(char *token);
t_token		*create_token(char *token);
void		add_token(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
void		tokenize_prompt(t_terminal *terminal, t_token **tokens);
// tokenize

// utils
int			is_special_chars(char *set);
void		copynstr(char *dest, char *src, size_t len);
void		put_separator(char **dest, char **src, int *pos);
void		print_token(t_token *token);
void		visualize_tokens(t_token *tokens);
// utils

// utils 2
bool		is_redirect_token(t_token_types token_id);
bool		is_token_sequence_invalid(t_token *token);
bool		is_pipe_sequence_invalid(t_token *token);
bool		is_redirect_invalid(t_token *token);
bool		tokens_checker(t_terminal *terminal);
// utils 2

// utils 3
int			is_built_in(char *token);
// utils 3

// env_utils
t_env	*structure_tail_node(t_env *env);
void	add_node_tail(t_env **head, t_env *new_structure);
t_env	*new_node(char *env_path);
t_env	*env_structure(char *env_path, t_env *env);
void	free_env_list(t_env **env_structure);
// env_utils
#endif
