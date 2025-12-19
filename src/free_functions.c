#include "minishell.h"

void	free_all(t_total_info **total)
{
	if (*total)
	{
		if ((*total)->token)
		{
			ft_token_clear(&(*total)->token);
			(*total)->token = NULL;
		}
		if ((*total)->cmds)
		{
			ft_cmds_clear(&(*total)->cmds);
			(*total)->cmds = NULL;
		}
		free(*total);
	}
}
