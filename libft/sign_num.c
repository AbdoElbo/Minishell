/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:17:40 by hkonstan          #+#    #+#             */
/*   Updated: 2025/07/22 18:39:52 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sign_num(int n)
{
	char	num[12];
	int		i;
	int		sum;

	sum = 0;
	i = 0;
	if (n < 0)
	{
		sum += write(1, "-", 1);
		if (n == -2147483648)
			return (sum + write(1, "2147483648", 10));
		n = -n;
	}
	else if (n == 0)
		return (write(1, "0", 1));
	while (n > 0)
	{
		num[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i > 0)
		sum += write(1, &num[--i], 1);
	return (sum);
}
