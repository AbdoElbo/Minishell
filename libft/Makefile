####################################### BEG_2 ####

NAME        := libft.a

BONUS=1

SRCS := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c\
	ft_lstiter_bonus.c ft_lstmap_bonus.c get_next_line.c \
	ft_printf.c character.c string.c sign_num.c  write_char.c \
	type_check.c unsign_num.c hex_lower.c hex_upper.c pointer.c 

# I could just use ":.c =.o but patsubst is more proper way replace patterns.
OBJS := $(patsubst %.c, %.o, $(SRCS))

CC := cc

CFLAGS := -Wall -Wextra -Werror -g

# -I is not neccassary since by default it checks the root directory but i use it.
LIBFLAGS := -I .

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove

RM          := rm -f

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   linking .o -> binary
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
	ar rcsUu $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all



