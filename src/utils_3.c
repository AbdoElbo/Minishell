
#include "minishell.h"

static int	count_cmds(t_token *lst)
{
	int i;
	i = 1;

	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->type == PIPE)
			i++;
		lst = lst->next;
	}
	i++;
	return (i);
}

static t_cmds	**init_structs(t_token *lst)
{
	t_cmds	**cmds;
	int		cmd_count;
	int		i;

	i = 0;
	cmd_count = count_cmds(lst);
	cmds = ft_calloc(cmd_count + 1, sizeof(t_cmds *));
	while (i < cmd_count)
	{
		cmds[i] = ft_calloc(1, sizeof(t_cmds *));
		if (!cmds[i])
		{
			write(2, "Mem alloc in init structs failed", 32);
			return (NULL); //free the cmds **
		}
		i++;
	}
	if (!cmds)
		write(2, "Mem alloc in init structs failed", 32);
	return (cmds);
}

t_cmds	**get_cmds(t_token *lst)
{
	t_cmds	**cmds;
	int 	i;

	i = 0;
	cmds = init_structs(lst);
	if (!cmds)
		return (NULL);
	if (lst)
	{
		while (lst)
		{			
			printf("%i\n", i);
			while (lst && lst->type != PIPE)
			{
				if (lst->type == WORD)
				{
					(cmds[i])->cmd = ft_strjoin(cmds[i]->cmd, lst->value);
					if (!((cmds[i])->cmd))
						return (NULL); //free all the structs and their values also.
				}
				while (lst && lst->type != WORD && lst->type != PIPE)
					lst = lst->next;
			}
			i++;
		}
	}
	i = 0;
	while (cmds[i])
		printf("%s\n", cmds[i++]->cmd);
	return (cmds);
}
