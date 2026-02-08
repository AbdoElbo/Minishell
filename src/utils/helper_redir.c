
#include "lists.h"

int	ft_redir_size(t_redir *redir)
{
	int	i;

	i = 0;
	if (redir == NULL)
		return (i);
	i++;
	while (redir->next != NULL)
	{
		i++;
		redir = redir->next;
	}
	return (i);
}

void	ft_redir_delone(t_redir *redir)
{
	if (redir != NULL)
	{
		free(redir->file);
		redir->file = NULL;
		redir->next = NULL;
		free(redir);
		redir = NULL;
	}
}

void	ft_redir_clear(t_redir **redir)
{
	t_redir	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (redir != NULL)
	{
		i = ft_redir_size(*redir);
		while (i > 0)
		{
			temp = (*redir)->next;
			ft_redir_delone(*redir);
			*redir = temp;
			i--;
		}
	}
}

t_redir	*ft_redir_last(t_redir *redir)
{
	if (redir == NULL)
		return (NULL);
	while (redir->next != NULL)
		redir = redir->next;
	return (redir);
}

void	ft_redir_addback(t_redir **redir, t_redir *new)
{
	t_redir	*temp;

	if (redir != NULL)
	{
		if (*redir == NULL)
			*redir = new;
		else
		{
			temp = ft_redir_last(*redir);
			temp->next = new;
		}
	}
}
