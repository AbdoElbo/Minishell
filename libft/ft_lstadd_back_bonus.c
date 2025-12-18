/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:51:32 by hkonstan          #+#    #+#             */
/*   Updated: 2025/12/18 13:14:28 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = ft_lstlast(*lst);
			temp->next = new;
		}
	}
}

void	ft_lstadd_back_2(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = ft_lstlast_2(*lst);
			temp->next = new;
		}
	}
}