
#include "minishell.h"

int	find_parameter(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < size)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((unsigned char)s1[i] != '=')
		return (1);
	return (0);
}

t_redir	*ft_lstlast_3(t_redir *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_3(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = ft_lstlast_3(*lst);
			temp->next = new;
		}
	}
}

t_cmds	*ft_lstlast_4(t_cmds *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_4(t_cmds **lst, t_cmds *new)
{
	t_cmds	*temp;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = ft_lstlast_4(*lst);
			temp->next = new;
		}
	}
}
