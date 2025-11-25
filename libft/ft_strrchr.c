/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:45:45 by hariskon          #+#    #+#             */
/*   Updated: 2025/05/05 16:22:56 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(char *letter, int a)
{
	char	*pointer;

	pointer = NULL;
	while (*letter)
	{
		if (*letter == (char)a)
			pointer = letter;
		letter++;
	}
	if ((char)a == '\0')
		return (letter);
	return (pointer);
}
