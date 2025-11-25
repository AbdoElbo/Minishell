/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:46:30 by hariskon          #+#    #+#             */
/*   Updated: 2025/05/13 14:41:28 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	num[10];
	int		i;

	i = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
			write(fd, "2147483648", 10);
		else
			n = -n;
	}
	else if (n == 0)
		write(fd, "0", 1);
	while (n > 0)
	{
		num[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i > 0)
		write(fd, &num[--i], 1);
}
