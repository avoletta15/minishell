NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address,undefined
READLINE_FLAGS = -lreadline -lncurses -L .brew/opt/readline/lib -I .brew/opt/readline/include
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = libft/inc
INCLUDES = includes/
INC_FLAGS = -I $(LIBFT_INC) -I $(INCLUDES)
ALL_FLAGS = $(CFLAGS) $(READLINE_FLAGS) $(INC_FLAGS) -L$(LIBFT_DIR) -lft

## DIRECTORIES ##
ENV = 		env/env_management.c env/env_utils.c env/env_utils2.c
HELPER = 	helper/helpers.c helper/helpers2.c
PARSER = 	parser/args_redirects.c parser/lexer.c parser/parser.c\
			parser/prompt_treatment.c parser/tokenize.c
UTILS = 	utils/error.c utils/error2.c utils/init_vars.c utils/memory.c utils/memory2.c\
			utils/utils.c utils/utils2.c utils/utils3.c utils/utils4.c utils/utils5.c
EXPANDER =	expander/expander.c expander/exp_util.c expander/exp_util2.c\
			expander/exp_util3.c
EXECUTOR = 	executor/mini_executor.c executor/handle_redir.c executor/executor_utils.c
HERE_DOC = 	executor/here_doc/here_doc.c /executor/here_doc/here_doc_errors.c\
			executor/here_doc/here_doc_utils.c
BUILTINS = 	executor/builtins/echo.c executor/builtins/cd.c executor/builtins/pwd.c\
			executor/builtins/env.c executor/builtins/errors.c executor/builtins/export.c\
			executor/builtins/unset.c executor/builtins/exit.c executor/builtins/errors2.c\
			executor/builtins/exec_builtins.c
SIGNALS = 	signal/child_signal.c signal/parent_signals.c
MAIN = 		minishell.c

SRC_DIR = src/
SRC = 	$(MAIN:%=$(SRC_DIR)%) $(ENV:%=$(SRC_DIR)%) $(HELPER:%=$(SRC_DIR)%) $(PARSER:%=$(SRC_DIR)%)\
		$(UTILS:%=$(SRC_DIR)%) $(EXECUTOR:%=$(SRC_DIR)%)\
		$(BUILTINS:%=$(SRC_DIR)%) $(HERE_DOC:%=$(SRC_DIR)%) $(SIGNALS:%=$(SRC_DIR)%) $(EXPANDER:%=$(SRC_DIR)%)
OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:$(SRC_DIR)%.c=%.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(ALL_FLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR) valgrind_log.txt readline.supp $(NAME).dSYM .vscode
	@make -s clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make -s fclean -C $(LIBFT_DIR)

re: fclean all

run: re
	@ ./minishell

v: re readline.supp
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --suppressions=readline.supp ./minishell
vv: $(NAME) readline.supp
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --suppressions=readline.supp ./minishell

readline.supp:
	@wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp 2> /dev/null 1> /dev/null


# ls | wc | echo " test $HOME '$PWD'    " >> text.txt hello this is my test

# cat Makefile | ls | echo "  $HOME 'test $PWD' $abc  " | wc
# cat\1Makefile\1|\1ls\1|\1echo\1"  $HOME 'test $PWD' $abc  "\1|\1wc
# cat\1Makefile\1\3\1ls\1\3\1echo\1"  $HOME 'test $PWD' $abc  "\1\3\1wc
# { "cat\1Makefile\1", "\1ls\1", "\1echo\1"  $HOME 'test $PWD' $abc  "\1", "\1wc" }
# { { "cat", "Makefile" }, { "ls" }, { "echo", ""  $HOME 'test $PWD' $abc  "" }, { "wc" } }
# { "cat\1Makefile\1", "\1ls\1", "\1echo\1"  $HOME 'test $PWD' $abc  "\1", "\1wc" }
# cat\2Makefile \3 ls\3 echo "  $HOME 'test $PWD' $abc  "\3 wc

# < Makefile cat
#\1<\1Makefile\1cat
# { "<", "Makefile", "cat" }

# struct elem {
# 	char **args = { "'<'", "$a", "cat" };
# 	struct elem *prev;
# 	struct elem *next;
# };