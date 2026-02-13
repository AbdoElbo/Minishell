
#ifndef EXPAND_H
# define EXPAND_H

# include "lists.h"

typedef enum e_state
{
	NORMAL,
	SQUOTE, // >
	DQUOTE, // >>
}	t_state;

typedef struct s_expand
{
	char			*redir_file;
	char			*str;
	int				arg_index;
	char			*temp;
	char			*r_temp;
	int				str_size;
	int				redir_size;
	int				i;
	int				i_redir;
	t_state			state;
}	t_expand;

int		expand_one_redir(t_total_info *total, t_cmds *cmds, t_expand *data);
int		expand_var(t_total_info *total, t_expand *data);
void	char_append(char *temp, char c);
int		increase_buffer(char **temp, int *size, int var_len);
int		expand_one_cmd(t_total_info *total, t_cmds *cmds, t_expand *data);
int		expand(t_total_info *total);

int		expand_var_redir(t_total_info *total, t_expand *data);
#endif
