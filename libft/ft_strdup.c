/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:48:19 by hariskon          #+#    #+#             */
/*   Updated: 2025/05/02 17:50:19 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*new_string;

	len = ft_strlen(src) + 1;
	new_string = malloc(len);
	if (new_string == NULL)
		return (NULL);
	ft_memcpy(new_string, src, len);
	return (new_string);
}
