
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

typedef struct s_redir
{
	char			*file;
	t_type			type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmds
{
	char			**argv;
	t_type			*type;
	t_redir			*redir;
	struct s_cmds	*next;
}	t_cmds;

int			find_parameter(const char *s1, const char *s2, size_t size);
t_token		*parse_input(char *line);
t_token		*ft_lstlast_2(t_token *lst);
void		ft_lstadd_back_2(t_token **lst, t_token *new);
t_token		*new_node(char *str, int len);
void		print_lst(t_token *lst);
int			is_operator(char c);

t_redir		*ft_lstlast_3(t_redir *lst);
void		ft_lstadd_back_3(t_redir **lst, t_redir *new);
t_cmds		*ft_lstlast_4(t_cmds *lst);
void		ft_lstadd_back_4(t_cmds **lst, t_cmds *new);
t_cmds		*get_cmds(t_token *lst);
void		print_cmds(t_cmds *lst);
int			check_lst_syntax(t_token *lst);

#endif
