/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:16:07 by hariskon          #+#    #+#             */
/*   Updated: 2025/05/03 15:26:50 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	destlen;
	size_t	i;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	i = 0;
	if (size <= destlen)
		return (size + srclen);
	while (destlen + i + 1 < size && src[i])
	{
		dest[destlen + i] = src[i];
		i++;
	}
	if (size != 0)
		dest[destlen + i] = '\0';
	return (destlen + srclen);
}
