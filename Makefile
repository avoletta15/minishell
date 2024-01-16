NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address,undefined
READLINE_FLAGS =  -lreadline -lncurses
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = libft/inc
INC_FLAGS = -I $(LIBFT_INC) -I ./
ALL_FLAGS = $(CFLAGS) $(READLINE_FLAGS) $(INC_FLAGS) -L$(LIBFT_DIR) -lft

SRC = 	prompt_treatment.c init_vars.c lexer.c utils.c\
		utils2.c memory.c error.c tokenize.c\
		parser.c args_redirects.c helpers.c memory2.c\
		helpers2.c utils3.c
ROOT_DIR = ./
OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(NAME).c -o $(NAME) $(OBJS) $(ALL_FLAGS)

$(OBJ_DIR)%.o: $(ROOT_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) $^ -o $@

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
	@valgrind --show-leak-kinds=all --leak-check=full --suppressions=readline.supp --log-file="valgrind_log.txt" ./minishell

readline.supp:
	@wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp 2> /dev/null 1> /dev/null

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