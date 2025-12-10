
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

typedef struct  s_cmds {
    char            **cmd;
    t_type          *type;
    char            **redir_file;
}   t_cmds;

void        sig_handler(int sig, siginfo_t *info, void *ucontext);
int	        find_parameter(const char *s1, const char *s2, size_t size);
t_token     *parse_input(char *line);
t_token	    *ft_lstlast_2(t_token *lst);
void	    ft_lstadd_back_2(t_token **lst, t_token *new);
t_token     *new_node(char *str, int len);
void        print_lst(t_token *lst);
int         is_operator(char c);

t_cmds      **get_cmds(t_token *lst);
int		    check_lst_syntax(t_token *lst);

#endif
