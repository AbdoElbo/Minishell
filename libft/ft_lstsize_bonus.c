/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:33:23 by hkonstan          #+#    #+#             */
/*   Updated: 2025/12/05 16:23:14 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
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

int	ft_lstsize_2(t_token *lst)
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