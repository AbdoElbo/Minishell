/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:48:53 by hariskon          #+#    #+#             */
/*   Updated: 2025/05/15 17:28:01 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t size)
{
	size_t	h;
	size_t	n;

	h = 0;
	n = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (h < size && haystack[h] != '\0')
	{
		while (haystack[h + n] == needle[n]
			&& (h + n) < size)
		{
			n++;
			if (needle[n] == '\0')
				return ((char *)(&haystack[h]));
		}
		n = 0;
		h++;
	}
	return (NULL);
}
