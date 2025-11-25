/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:04:46 by hkonstan          #+#    #+#             */
/*   Updated: 2025/07/22 18:39:59 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	type_check(va_list args, char c)
{
	int	sum;

	sum = 0;
	if (c == 'c')
		sum += character(va_arg(args, int));
	else if (c == 's')
		sum += string(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		sum += sign_num(va_arg(args, int));
	else if (c == 'u')
		sum += unsign_num(va_arg(args, int));
	else if (c == '%')
		sum += character('%');
	else if (c == 'x')
		sum += hex_lower(va_arg(args, unsigned int));
	else if (c == 'X')
		sum += hex_upper(va_arg(args, unsigned int));
	else if (c == 'p')
		sum += pointer(va_arg(args, void *));
	return (sum);
}
