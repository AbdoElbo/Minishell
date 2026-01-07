
NAME	:= minishell
CFLAGS	:= -Wextra -Wall -Werror -g

GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

HEADERS	:= -I ./include

SRCS	:= src/minishell.c src/helper_func_1.c src/utils_1.c src/utils_2.c \
			src/utils_3.c src/abdo_signals.c src/abdo_builtins_1.c \
			src/abdo_builtins_2.c
OBJS 	:= $(SRCS:.c=.o)

LIBFT_DIR  := ./libft
LIBFT  := $(LIBFT_DIR)/libft.a

all: libft $(NAME)

MSG:
	@printf "Compiling Minishell"

%.o: %.c Makefile
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "."

$(NAME): MSG $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) $(HEADERS) -lreadline -o $(NAME)

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@printf "$(BLUE)Cleaned Up$(RESET)\n"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft bonus
