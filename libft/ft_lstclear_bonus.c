/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:58:46 by hkonstan          #+#    #+#             */
/*   Updated: 2025/12/05 16:40:46 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (lst != NULL)
	{
		i = ft_lstsize(*lst);
		while (i > 0)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
			i--;
		}
	}
}

void	ft_lstclear_2(t_token **lst)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (lst != NULL)
	{
		i = ft_lstsize_2(*lst);
		while (i > 0)
		{
			temp = (*lst)->next;
			ft_lstdelone_2(*lst);
			*lst = temp;
			i--;
		}
	}
}
