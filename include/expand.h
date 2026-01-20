
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
	char			*str;
	int				arg_index;
	char			*temp;
	int				str_size;
	int				i;
	t_state			state;
}	t_expand;

void	char_append(char *temp, char c);
int		normal(t_expand *token, t_cmds *cmds);
int		squote(t_expand *data, t_cmds *cmds);
int		dquote(t_expand *data, t_cmds *cmds);
void	is_quote_space(int *space_c, int *i, t_cmds *cmds, char *temp);
int		expand(t_total_info *total);

#endif