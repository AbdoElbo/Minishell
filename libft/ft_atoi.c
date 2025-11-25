/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:49:00 by hariskon          #+#    #+#             */
/*   Updated: 2025/07/09 13:41:10 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char a);

long	ft_atoi(const char *str)
{
	int		i;
	int		symbol;
	long	result;

	i = 0;
	symbol = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			symbol = -symbol;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (ft_strlen(str) > 11)
		return (__LONG_MAX__);
	return (result * symbol);
}

static int	ft_isspace(char a)
{
	if (a == ' ' || a == '\f' || a == '\n'
		|| a == '\r' || a == '\t' || a == '\v')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
