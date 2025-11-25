/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsign_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:32:17 by hkonstan          #+#    #+#             */
/*   Updated: 2025/07/22 18:40:03 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	unsign_num(unsigned int n)
{
	char	num[15];
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (n == 0)
		count += write(1, "0", 1);
	while (n > 0)
	{
		num[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i > 0)
		count += write(1, &num[--i], 1);
	return (count);
}
