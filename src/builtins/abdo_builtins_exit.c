/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abdo_builtins_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:19:08 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/22 20:30:38 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abdo.h"
#include <limits.h>

// returns 1 if the string is variation of :
// -n or -nnnn or -nnnnnnnnn...
// returns 0 if the string should be treated as a string (no newline)
static long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	check_number(long long result, char *s, int i, int sign)
{
	i++;
	if (sign == 1)
	{
		if (result > 922337203685477580 && s[i])
			return (1);
		else if (result == 922337203685477580 && (s[i] && s[i] >= '8'))
			return (1);
		else if (result > 100000000000000000 && (s[i] && (s[i + 1])))
			return (1);
	}
	else
	{
		if (result > 922337203685477580 && (s[i] && s[i] >= '0' && s[i] <= '9'))
			return (1);
		else if (result == 922337203685477580 && (s[i] && s[i] == '9'))
			return (1);
		else if (result > 100000000000000000 && (s[i] && (s[i + 1])))
			return (1);
	}
	return (0);
}

static int	its_over(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (check_number(result, (char *)str, i, sign))
			return (1);
		i++;
	}
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	if (its_over(argv[1]))
// 	{
// 		write(2, "Error:\nLONG_Overflow.\n", 22);
// 		return (0);
// 	}
// 	else
// 		printf("%lli\n", (ft_atoll(argv[1]) % 256));
// 	return (0);
// }

// every exit returns the value modulo 256
// example: exit 1000 --> 1000 % 256 = 232
// so the return value is 232
// but the limit is up to LONG_MAX, if LONG MAX is reached, we print the following :
// bash: exit: *INSERT NUMBER HERE*: numeric argument required
int		builtin_exit(char *env)
{

}
