
#ifndef HARIS_H
# define HARIS_H

# include "lists.h"

typedef struct s_total_info
{
	t_token			*token;
	t_cmds			*cmds;
	char			**our_envp;
}	t_total_info;

void	free_all(t_total_info **total);
int		expand(t_total_info *total, char **envp);

#endif
