/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:12:44 by hariskon          #+#    #+#             */
/*   Updated: 2025/05/02 17:49:58 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_memcmp(const void *array1, const void *array2, size_t size)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while (i < size)
	{
		if (((unsigned char *)array1)[i] != ((unsigned char *)array2)[i])
		{
			a = ((unsigned char *)array1)[i];
			b = ((unsigned char *)array2)[i];
			return (a - b);
		}
		else
		{
			i++;
		}
	}
	return (0);
}
