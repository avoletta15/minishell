NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
READLINE_FLAGS = -lreadline -lncurses
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = libft/inc
INCLUDES = includes/
INC_FLAGS = -I $(LIBFT_INC) -I $(INCLUDES)
ALL_FLAGS = $(CFLAGS) $(READLINE_FLAGS) $(INC_FLAGS) -L$(LIBFT_DIR) -lft

## DIRECTORIES ##
ENV = 		env/env_management.c env/env_utils.c
HELPER = 	helper/helpers.c helper/helpers2.c
PARSER = 	parser/args_redirects.c parser/lexer.c parser/parser.c\
			parser/prompt_treatment.c parser/tokenize.c
UTILS = 	utils/error.c utils/init_vars.c utils/memory.c utils/memory2.c\
			utils/utils.c utils/utils2.c utils/utils3.c
EXPANDER =	expander/expander.c expander/expand_utils.c expander/expand_free.c\
			expander/expander_refact.c
EXECUTOR = 	executor/mini_executor.c
BUILTINS = 	executor/builtins/echo.c executor/builtins/cd.c executor/builtins/pwd.c\
			executor/builtins/env.c

SRC_DIR = src/
SRC = 	$(ENV:%=$(SRC_DIR)%) $(HELPER:%=$(SRC_DIR)%) $(PARSER:%=$(SRC_DIR)%)\
		$(UTILS:%=$(SRC_DIR)%) $(EXPANDER:%=$(SRC_DIR)%) $(EXECUTOR:%=$(SRC_DIR)%)\
		$(BUILTINS:%=$(SRC_DIR)%)
OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:$(SRC_DIR)%.c=%.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(SRC_DIR)$(NAME).c -o $(NAME) $(OBJS) $(ALL_FLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) $< -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR) valgrind_log.txt readline.supp $(NAME).dSYM
	@make -s clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make -s fclean -C $(LIBFT_DIR)

re: fclean all

run: re
	@ ./minishell

v: re readline.supp
	@valgrind --show-leak-kinds=all --leak-check=full --suppressions=readline.supp ./minishell

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