/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:18:16 by hariskon          #+#    #+#             */
/*   Updated: 2025/07/22 18:39:55 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	string(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		i = 6;
		write(1, "(null)", 6);
		return (i);
	}
	while (str[i] != '\0')
		character(str[i++]);
	return (i);
}
