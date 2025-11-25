/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:08:36 by hkonstan          #+#    #+#             */
/*   Updated: 2025/05/15 13:05:55 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void*))
{
	t_list	*n_list;
	t_list	*n_node;
	int		len;
	void	*new_content;

	n_node = NULL;
	n_list = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	len = ft_lstsize(lst);
	while (len-- > 0)
	{
		new_content = f(lst->content);
		n_node = ft_lstnew(new_content);
		if (n_node == NULL)
		{
			del(new_content);
			ft_lstclear(&n_list, del);
			return (NULL);
		}
		ft_lstadd_back(&n_list, n_node);
		lst = lst->next;
	}
	return (n_list);
}
