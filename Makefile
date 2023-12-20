NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE_FLAGS =  -lreadline -lncurses
LIBFT_DIR = libft/
LIBFT_INC = libft/inc
INC_FLAGS = -I $(LIBFT_INC)
ALL_FLAGS = $(CFLAGS) $(READLINE_FLAGS) $(INC_FLAGS) -L$(LIBFT_DIR) -lft

SRC = prompt_treatment.c init_vars.c lexer.c
ROOT_DIR = ./
OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(NAME).c -o $(NAME) $(OBJS) $(ALL_FLAGS)

$(OBJ_DIR)%.o: $(ROOT_DIR)%.c
	@make -C $(LIBFT_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) $^ -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all
