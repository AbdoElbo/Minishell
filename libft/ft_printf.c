/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:01:59 by hariskon          #+#    #+#             */
/*   Updated: 2025/07/22 18:40:34 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	size_t	i;
	int		sum;
	va_list	args;

	va_start (args, format);
	i = 0;
	sum = 0;
	if (format == NULL)
		return (-1);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
			sum += write(1, &format[i++], 1);
		else
		{
			sum += type_check(args, format[++i]);
			i++;
		}
	}
	va_end(args);
	return (sum);
}
