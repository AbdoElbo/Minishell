/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:33:29 by hariskon          #+#    #+#             */
/*   Updated: 2025/11/07 15:38:42 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (*array)
	{
		array++;
		i++;
	}
	return (i);
}
