/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:52:10 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/21 01:30:15 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <exit_status.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PARSER_SEP '\1'
# define DOUBLE_QUOTE '\2'
# define SINGLE_QUOTE '\3'

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
	ARGS_ID,
}			t_token_types;

typedef struct s_quotes_system
{
	char	*prompt;
	char	**prompt_splitted;
	char	quote;
	bool	quote_state;
}				t_quotes_system;

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
typedef struct s_args
{
	t_token_types	toked_id;
	char			*args;
	struct s_args	*next;
}				t_args;

typedef struct s_redirect
{
	t_token_types		toked_id;
	char				*content;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_command
{
	char				*cmd_path;
	char				**args;
	int					fd[2];
	t_redirect			*redirections;
	struct s_command	*next;
}				t_command;

typedef struct s_program
{
	char				*prompt;
	char				**prompt_splitted;
	t_command			*commands;
	t_token				*tokens;
	t_args				*args;
	t_redirect			*redirects;
	t_env				*env;
	int					exit_status;
	t_quotes_system		quotes_system;
}				t_terminal;

// args_redirects
t_args		*create_args(t_token *token);
t_redirect	*create_redirect(t_token *token);
void		add_arg(t_terminal *terminal, t_token *token);
void		add_redirect(t_terminal *terminal, t_token *token);
// args_redirects

// error
void		unclosed_quote_error(void);
void		malloc_error(void);
void		bad_syntax_error(char *str);
void		invalid_token_error(t_terminal *terminal, char *str);
// error

// init vars
void		reset_terminal(t_terminal *terminal, int exit_status);
void		init_terminal(t_terminal *terminal, int exit_status);
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
void		subsquote(char *new_prompt, t_quotes_system *quote);
// prompt treatment

// memory
void		free_prompt(char **prompt_splitted);
void		free_tokens(t_token *tokens);
void		free_args(t_args *arg);
void		free_redirect(t_redirect *redirect);
void		free_redir_args(t_terminal *terminal);
// memory

// memory 2
void		free_commands(t_terminal *terminal);
void		free_structs(t_terminal *terminal,
				bool should_exit, void (*call_back)(void));
// memory 2

// parser
bool		parser(t_terminal *terminal);
size_t		count_args(t_terminal *terminal);
// parser

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
bool		only_white_spaces(char *str);
// utils

// utils 2
bool		is_redirect_token(t_token_types token_id);
bool		is_token_sequence_invalid(t_token *token);
bool		is_pipe_sequence_invalid(t_token *token);
bool		is_redirect_invalid(t_token *token);
bool		tokens_checker(t_terminal *terminal);
// utils 2

// env_utils
t_env	*structure_tail_node(t_env *env);
void	add_node_tail(t_env **head, t_env *new_structure);
t_env	*new_node(char *env_path);
t_env	*env_structure(char *env_path, t_env *env);
void	free_env_list(t_env **env_structure);
// env_utils
// helpers
void		print_token(t_token *token);
void		visualize_tokens(t_token *tokens);
void		print_args(char **args);
void		print_redir(t_redirect *redirect);
// helpers

// helpers 2
void		put_cmd(char *str);
void		printf_command(t_command *command);
void		visualize_commands(t_command *command);
void		visualise_expanded_var(t_terminal *terminal);
// helpers 2

// expander
char	*ft_expansion_check(t_terminal *terminal, char flag);
char	ft_checking_quotes(char c, char flag);
char	*ft_should_expand(char *str, int *i, t_terminal *terminal);
char	*ft_search_variable(char *var, t_terminal *terminal);
char	*variable_alias(char *str);
bool	ft_forbidden_expansion(char c, int i);
// expander

#endif
