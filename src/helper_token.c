
#include "lists.h"
#include "minishell.h"

int	ft_token_size(t_token *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (i);
	i++;
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_token_delone(t_token *lst)
{
	if (lst != NULL)
	{
		free(lst->value);
		lst->value = NULL;
		lst->next = NULL;
		free(lst);
		lst = NULL;
	}
}

void	ft_token_clear(t_token **lst)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (lst != NULL)
	{
		i = ft_token_size(*lst);
		while (i > 0)
		{
			temp = (*lst)->next;
			ft_token_delone(*lst);
			*lst = temp;
			i--;
		}
	}
	*lst = NULL;
}

t_token	*ft_token_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_token_addback(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = ft_token_last(*lst);
			temp->next = new;
		}
	}
}
