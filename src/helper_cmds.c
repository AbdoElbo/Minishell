
#include "minishell.h"

int	ft_cmds_size(t_cmds *cmds)
{
	int	i;

	i = 0;
	if (cmds == NULL)
		return (i);
	i++;
	while (cmds->next != NULL)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	ft_cmds_delone(t_cmds *cmds)
{
	int	i;

	if (cmds != NULL)
	{
		i = 0;
		while (cmds->argv[i])
		{
			free(cmds->argv[i]);
			i++;
		}
		free(cmds->argv);
		ft_redir_clear(&cmds->redir);
		free(cmds->whole_cmd);
		cmds->whole_cmd = NULL;
		cmds->argv = NULL;
		cmds->redir = NULL;
		cmds->next = NULL;
		free(cmds);
	}
}

void	ft_cmds_clear(t_cmds **cmds)
{
	t_cmds	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (cmds != NULL)
	{
		i = ft_cmds_size(*cmds);
		while (i > 0)
		{
			temp = (*cmds)->next;
			ft_cmds_delone(*cmds);
			*cmds = temp;
			i--;
		}
	}
}

t_cmds	*ft_cmds_last(t_cmds *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_cmds_addback(t_cmds **lst, t_cmds *new)
{
	t_cmds	*temp;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = ft_cmds_last(*lst);
			temp->next = new;
		}
	}
}
