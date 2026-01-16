
#ifndef HARIS_H
# define HARIS_H

# include "lists.h"

typedef struct s_total_info
{
	t_token			*token;
	t_cmds			*cmds;
	t_envp			*our_envp;
}	t_total_info;

typedef enum e_state
{
	NORMAL,
	SQUOTE, // >
	DQUOTE, // >>
}	t_state;

void	free_all(t_total_info **total);
void	free_arr(char **arr);
int		expand(t_total_info *total);

#endif
