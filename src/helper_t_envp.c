
#include "lists.h"

int	ft_t_envp_size(t_envp *envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (i);
	i++;
	while (envp->next != NULL)
	{
		i++;
		envp = envp->next;
	}
	return (i);
}

void	ft_t_envp_delone(t_envp *envp)
{
	if (envp != NULL)
	{
		free(envp->string);
		envp->string = NULL;
		envp->next = NULL;
		free(envp);
		envp = NULL;
	}
}

void	ft_t_envp_clear(t_envp **envp)
{
	t_envp	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (envp != NULL)
	{
		i = ft_t_envp_size(*envp);
		while (i > 0)
		{
			temp = (*envp)->next;
			ft_t_envp_delone(*envp);
			*envp = temp;
			i--;
		}
	}
}

t_envp	*ft_t_envp_last(t_envp *envp)
{
	if (envp == NULL)
		return (NULL);
	while (envp->next != NULL)
		envp = envp->next;
	return (envp);
}

void	ft_t_envp_addback(t_envp **envp, t_envp *new)
{
	t_envp	*temp;

	if (envp != NULL)
	{
		if (*envp == NULL)
			*envp = new;
		else
		{
			temp = ft_t_envp_last(*envp);
			temp->next = new;
		}
	}
}
