/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:39:39 by hariskon          #+#    #+#             */
/*   Updated: 2025/05/13 12:27:53 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strchr(char *letter, int a)
{
	while (*letter)
	{
		if (*letter == (char)a)
			return (letter);
		else
			letter++;
	}
	if ((char)a == '\0')
		return (letter);
	return (NULL);
}
