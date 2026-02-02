
NAME	:= minishell
CFLAGS	:= -Wextra -Wall -Werror

HEADERS	:= -I ./include

SRCS	:= src/minishell.c src/__path_helper.c src/utils_1.c src/utils_2.c \
			src/utils_3.c src/abdo_signals.c src/helper_cmds.c src/helper_redir.c \
			src/helper_token.c src/free_functions.c src/expand.c src/helper_t_envp.c \
			src/expand_helper_1.c src/expand_helper_2.c src/expand_helper_3.c \
			src/pipex/pipex.c src/pipex/helpers.c src/pipex/parsing.c src/pipex/cleanup_utils.c \
			src/expand_redir.c src/expand_redir_helper.c \
			src/builtins/arr.c src/builtins/builtin_helper.c src/builtins/builtins_cd.c \
			src/builtins/builtins_echo.c src/builtins/builtins_exit.c \
			src/builtins/builtins_export_1.c src/builtins/builtins_export_sorted_1.c \
			src/builtins/builtins_export_sorted_2.c src/builtins/builtins_pwd_env.c \
			src/builtins/builtins_unset.c src/builtins/call_builtins.c

GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

OBJ_DIR	:= objects
OBJS 	:= $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT_DIR  := ./libft
LIBFT  := $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o : src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "$(GREEN).$(RESET)"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(HEADERS) -lreadline -o $(NAME)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@printf "$(BLUE)Cleaned Up$(RESET)\n"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
