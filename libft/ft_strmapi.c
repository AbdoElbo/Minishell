/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:20:28 by hariskon          #+#    #+#             */
/*   Updated: 2025/05/08 15:02:34 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*new_string;
	size_t			len;
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	new_string = malloc(len * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new_string[i] = f(i, (char)s[i]);
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
