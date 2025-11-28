# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/06 14:04:06 by hariskon          #+#    #+#              #
#    Updated: 2025/11/28 16:57:22 by aelbouaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CFLAGS	:= -Wextra -Wall -Werror -g

HEADERS	:= -I ./include

SRCS	:= src/abdo_test_main.c src/ft_split_pipe.c
OBJS 	:= $(SRCS:.c=.o)

LIBFT_DIR  := ./libft
LIBFT  := $(LIBFT_DIR)/libft.a

all: libft $(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(HEADERS) -lreadline -o $(NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft bonus
