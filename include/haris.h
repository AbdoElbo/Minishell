
#ifndef HARIS_H
# define HARIS_H

# include "lists.h"

typedef struct s_total_info
{
	t_token			*token;
	t_cmds			*cmds;
}	t_total_info;

void	free_all(t_total_info **total);

#endif
