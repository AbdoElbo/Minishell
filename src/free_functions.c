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
		if ((*total)->our_envp)
		{
			free((*total)->our_envp);
		}
		free(*total);
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
