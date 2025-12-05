/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:49:31 by hkonstan          #+#    #+#             */
/*   Updated: 2025/12/05 16:41:10 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*to_delete;

	to_delete = lst;
	if (lst != NULL)
	{
		del(to_delete->content);
		free(lst);
	}
}

void	ft_lstdelone_2(t_token *lst)
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