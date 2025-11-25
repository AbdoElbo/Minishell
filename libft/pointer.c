/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:03:31 by hkonstan          #+#    #+#             */
/*   Updated: 2025/07/22 18:39:47 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hex_cap(unsigned long long n)
{
	int	sum;

	sum = 1;
	if (n / 16 != 0 && n > 0)
	{
		sum += hex_cap(n / 16);
	}
	write (1, &"0123456789abcdef"[n % 16], 1);
	return (sum);
}

int	pointer(void *p)
{
	int					sum;
	unsigned long long	n;

	n = (unsigned long long)p;
	sum = 0;
	if (p == NULL)
	{
		sum = 5;
		write(1, "(nil)", 5);
		return (sum);
	}
	write(1, "0x", 2);
	sum += 2;
	sum += hex_cap(n);
	return (sum);
}
