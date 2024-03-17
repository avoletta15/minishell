/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marioliv <marioliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:21:35 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/17 17:05:39 by marioliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <errno.h>
# include <exit_status.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

# define PARSER_SEP 1
# define DOUBLE_QUOTE 2
# define SINGLE_QUOTE 3

# define PIPE "|"
# define INPUT_REDIRECT "<"
# define OUTPUT_REDIRECT ">"
# define HERE_DOC "<<"
# define APPEND ">>"
# define ECHO_STR "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

# define PROGRAM_NAME "minishell"

// MACRO ERRORS
# define UNCLOSED_QUOTE_ERROR "Error: unclosed quote\n"
# define MALLOC_ERROR "Error: Malloc failed\n"
# define BAD_SYNTAX_ERROR1 "minishell: bad syntax "
# define BAD_SYNTAX_ERROR2 "error near to the unexpected token "
# define NEW_LINE "newline"
# define CD_ARGS_COUNT_ERROR ": cd: Excessive number of arguments\n"
# define CD_HOME_NOT_FOUND_ERROR "cd: HOME not set\n"
# define INVALID_EXPORT_ERROR1 ": export: `"
# define INVALID_EXPORT_ERROR2 "\': not a valid identifier\n"
# define NO_SUCH_FILE_OR_DIR "No such file or directory\n"
// MACRO ERRORS

typedef enum e_builtin_types
{
	ECHO_ID = 1,
	CD_ID,
	PWD_ID,
	EXPORT_ID,
	UNSET_ID,
	ENV_ID,
	EXIT_ID,
}			t_builtin_types;

typedef enum e_token_types
{
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
	char	**array;
	char	quote;
	bool	quote_state;
	bool	was_quoted;
	size_t	i;
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
	char			*key;
	char			*value;
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
	bool				invalid_expansion;
	int					fd;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_std_fds
{
	int		in;
	int		out;
}				t_std_fds;

typedef struct s_command
{
	char				*cmd_path;
	char				**args;
	int					pipe_fd[2];
	t_std_fds			std_fds;
	pid_t				pid;
	t_redirect			*redirections;
	struct s_command	*next;
	struct s_command	*prev;
}				t_command;

typedef struct s_variables
{
	int			len;
	int			i;
	int			j;
	char		*var;
	char		*temp;
	char		*new_index;
	char		*key;
	bool		quoted;
}				t_vars;

typedef struct s_env_api
{
	t_env	*env_head;
	bool	(*new_env_var)(char *);
	bool	(*new_env_key_value)(char *, char *);
	bool	(*update_var)(t_env *, char *);
	void	(*remove_var)(char *);
	size_t	len;
	t_env	*(*getvar)(char *);
}			t_env_api;

typedef struct s_terminal
{
	char			*prompt;
	char			**prompt_splitted;
	t_command		*commands;
	t_token			*tokens;
	t_args			*args;
	t_redirect		*redirects;
	t_env			*env;
	unsigned char	exit_status;
	int				i;
	t_vars			vars;
	t_quotes_system	quotes_system;
	bool			hd_exit;
}				t_terminal;

// args_redirects
t_args			*create_args(t_token *token);
t_redirect		*create_redirect(t_token *token);
void			add_arg(t_terminal *terminal, t_token *token);
void			add_redirect(t_terminal *terminal, t_token *token);
// args_redirects

// error
void			unclosed_quote_error(void);
void			malloc_error(void);
void			bad_syntax_error(char *str);
void			invalid_token_error(t_terminal *terminal, char *str);
void			no_path_error(char *str);
// error

// error 2
bool			ambiguous_redir_error(char *content);
// error 2

// init vars
void			reset_terminal(t_terminal *terminal);
void			init_terminal(t_terminal *terminal);
void			init_quotes_system(t_quotes_system *quotes_system);
// init vars

// lexer
bool			first_filter(char *str, t_quotes_system *quotes);
bool			second_filter(t_terminal *terminal);
bool			third_filter(t_terminal *terminal);
bool			lexer(t_terminal *terminal);
// lexer

// prompt treatment
void			remove_whitespaces(char *src,
					t_quotes_system *quotes);
void			delimit_special_chars(char *dest,
					char *src, t_quotes_system *quote);
void			subsquote(char *new_prompt, t_quotes_system *quote);
// prompt treatment

// memory
void			free_array(char **array);
void			free_tokens(t_token *tokens);
void			free_args(t_args *arg);
void			free_redirect(t_redirect *redirect);
void			free_redir_args(t_terminal *terminal);
// memory

// memory 2
void			free_commands(t_terminal *terminal);
void			free_structs(t_terminal *terminal,
					bool should_exit, void (*call_back)(void));
void			free_terminal(t_terminal *terminal);
void			ft_protection_free(t_terminal *terminal, char *var);
// memory 2

// parser
bool			parser(t_terminal *terminal);
size_t			count_args(t_terminal *terminal);
// parser

// tokenize
int				get_token_id(char *token);
t_token			*create_token(char *token);
void			add_token(t_token **tokens, t_token *new_token);
void			free_tokens(t_token *tokens);
void			tokenize_prompt(t_terminal *terminal, t_token **tokens);
// tokenize

// utils
int				is_special_chars(char *set);
void			copynstr(char *dest, char *src, size_t len);
void			put_separator(char **dest, char **src, int *pos);
bool			only_white_spaces(char *str);
// utils

// utils 2
bool			is_redirect_token(t_token_types token_id);
bool			is_token_sequence_invalid(t_token *token);
bool			is_pipe_sequence_invalid(t_token *token);
bool			is_redirect_invalid(t_token *token);
bool			tokens_checker(t_terminal *terminal);
// utils 2

// utils 3
size_t			size_of_array(char **strs);
void			set_cmds_path(t_terminal *terminal);
bool			check_absolute_path(char *str);
// utils 3

// utils 4
t_builtin_types	is_builtin(char *cmd);
bool			is_a_single_builtin(t_command *cmd);
char			**convert_env_list_to_array(void);
void			close_fds(int in, int out);
// utils 4

// utils 5
void			close_cmds_fds(t_command *cmd, bool close_pipe);
t_terminal		*get_terminal(void);
void			quotes_iterator(t_quotes_system *quotes_sys, char c);
void			str_chr_subs(char *str, char sub, char to_replace);
// utils 5

// env
t_env_api		*env_api(void);
bool			init_env(t_terminal *terminal);
bool			build_minimum_env(t_terminal *terminal);
bool			check_new_env(char *str);
char			*get_var_key(char *str);
bool			is_var_key_char_valid(char c, int i);
// env

// env_utils
t_env			*structure_tail_node(t_env *env);
void			add_node_tail(t_env **head, t_env *new_structure);
t_env			*new_node(char *env_path);
t_env			*env_structure(char *env_path, t_env *env);
void			free_env_list(t_env **env_structure);
// env_utils

// env_utils 2
bool			new_env_var(char *env_path);
bool			new_env_key_value(char *key, char *value);
bool			update_var(t_env *env, char *str);
void			remove_var(char *var);
t_env			*getvar(char *var);
// env_utils 2

// helpers
void			print_token(t_token *token);
void			visualize_tokens(t_token *tokens);
void			print_args(char **args);
void			print_redir(t_redirect *redirect);
void			print_args(char **args);
// helpers

// helpers 2
void			printf_command(t_command *command);
void			visualize_commands(t_command *command);
void			visualise_expanded_var(t_terminal *terminal);
void			visualize_env(t_env *env, int out);
void			print_str(char *str);
// helpers 2

// expander
void			generic_expansion(t_terminal *terminal);
void			run_redirections(t_redirect *redir);
char			**run_the_array(char **array);
char			*expander(char *str, t_quotes_system *quotes_sys);
// expander

// exp_utils
size_t			quotes_count(char *str);
char			*remove_quotes(char *old);
char			*ft_strrep(char *str, size_t from, size_t len, char *add);
char			*join_the_array(char **array, char *separator);
// exp_utils

// exp_utils2
void			manipulate_str(char **str, char **array,
					t_quotes_system *quotes_sys);
char			*expand_str(char *str, t_quotes_system *quotes_sys,
					bool is_in_here_doc);
char			*exit_status_management(char *str, t_quotes_system *quotes_sys);
// exp_utils2

// exp_utils3
char			*expanded_vars(char *str, size_t *i, char *key);
int				get_var_len(char *str, size_t i);
char			*ft_search_variable(char *var);
char			*variable_alias(char *str);
bool			ft_forbidden_expansion(char c, int i);
// exp_utils3

// builtins
void			echo(char **av, int out, unsigned char *exit_status);
void			cd(char **dir_path, unsigned char *exit_status);
void			pwd(int out, unsigned char *exit_status);
void			env(t_env *env, int out, unsigned char *exit_status);
bool			cd_args_count_error(void);
bool			cd_fail(char *dir_path);
void			export_update_value_error(char *str);
void			export_unclosed_quotes(char *str);
void			env_args_count_error(unsigned char *exit_status);
void			exit_non_numeric_arg(char *str);
bool			export_invalid_identifier(char *str);
void			exit_wrong_args_num(void);
int				setpwds(t_env *oldpwd, t_env *envpwd, char *pwd);
void			export(char **args, int out, unsigned char *exit_status);
void			unset(char **args, unsigned char *exit_status);
void			mini_exit(t_terminal *terminal, char **args);
void			exec_builtins(t_terminal *terminal, char **args, int out);
// builtins

// handle redirect
bool			redirection_handle(t_command *cmd, bool parent);
int				handle_open(t_redirect *redir,
					int *in, int *out);
// handle redirect

// here doc
bool			here_doc(t_terminal *terminal);
void			here_doc_ctrl_d(char *delimiter);
void			here_doc_fork_error(int *fds);
// here doc

// here doc utils
void			remove_echoctl(struct termios *term,
					struct termios *original, bool *sigint);
void			here_doc_write_loop(char *line, char *delimiter,
					int fd, bool *sigint);
char			*manipulate_delimiter(char *delimiter);
// here doc utils

// executor
void			mini_executor(t_terminal *terminal);
void			choose_execve(t_terminal *terminal, t_command *cmd);
// executor

// signal
void			handle_child_signals(void);
void			handle_parent_execution_signals(void);
void			handle_parent_signals(void);
void			handle_heredoc_signals(void);
// signal

// new
char			**run_the_array(char **array);
void			generic_expansion(t_terminal *terminal);
char			*expand_str(char *str, t_quotes_system *quotes_sys,
					bool is_in_here_doc);
#endif
