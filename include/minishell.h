
#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include "../libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include "abdo.h"
# include "haris.h"
# include "lists.h"

typedef enum e_type t_type ;

int			find_parameter(const char *s1, const char *s2, size_t size);
t_token		*parse_input(char *line);
t_token		*new_node(char *str, int len);
void		print_lst(t_token *lst);
int			is_operator(char c);

t_cmds		*get_cmds(t_token *lst);
void		print_cmds(t_cmds *lst);
int			check_lst_syntax(t_token *lst);



#endif
