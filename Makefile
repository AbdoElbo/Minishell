
NAME	:= minishell
CFLAGS	:= -Wextra -Wall -Werror -g

HEADERS	:= -I ./include

SRCS	:= src/minishell.c src/__path_helper.c src/utils_1.c src/utils_2.c \
			src/utils_3.c src/abdo_signals.c src/helper_cmds.c src/helper_redir.c \
			src/helper_token.c src/free_functions.c src/expand.c src/helper_t_envp.c \
			src/expand_helper_1.c src/expand_helper_2.c

OBJ_DIR	:= objects
OBJS 	:= $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT_DIR  := ./libft
LIBFT  := $(LIBFT_DIR)/libft.a

all: libft $(NAME)

MSG:
	@printf "Compiling Minishell"

$(OBJ_DIR)/%.o: src/%.c Makefile | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "."

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): MSG $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) $(HEADERS) -lreadline -o $(NAME)

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@printf "$(BLUE)Cleaned Up$(BLUE)\n"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft bonus
