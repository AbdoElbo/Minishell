
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
# include "pipex.h"
# include "builtins.h"
# include "lists.h"
# include "haris.h"
# include "expand.h"

# define RED   "\001\033[1;31m\002"
# define RESET "\001\033[0m\002"

int				check_lst_type(t_token *lst);
int				finish_argv(int *arg_index, t_cmds *cmds, char *temp);
size_t			count_words(char **a);
t_total_info	*init_total(char **envp, int exit);
char			*ft_strjoin_arg(char const *s1, char const *s2);
t_token			*parse_input(char *line);
t_token			*new_node(char *str, int len);
int				return_i(char *redir_file);
void			print_lst(t_token *lst);
int				is_operator(char c);
int				copy_envp(t_total_info *total, char **envp);

int				get_cmds(t_total_info *total, t_token *lst);
void			check_our_envp(t_envp *our_envp, char **envp);
void			print_cmds(t_cmds *lst);

#endif
