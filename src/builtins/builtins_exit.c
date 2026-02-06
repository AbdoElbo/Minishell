/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:19:08 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/02/06 19:38:17 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <limits.h>

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

static int	its_over(const char *str, long long *result)
{
	int			i;
	int			sign;

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
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		(*result) = (*result) * 10 + (str[i] - '0');
		if (check_number((*result), (char *)str, i, sign))
			return (1);
		i++;
	}
	(*result) *= sign;
	return (0);
}

static int	all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	write_error(char *str)
{
	write(2, "exit: ", 6);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
}

int	builtin_exit(int argc, char **argv, t_total_info *total)
{
	long long	result;

	if (argc == 1)
		((void)free_all(&total), _exit(EXIT_SUCCESS));
	if (argc != 2)
	{
		write(2, "exit: too many arguments\n", 25);
		return (EXIT_FAILURE);
	}
	if (!all_digit(argv[1]))
	{
		write_error(argv[1]);
		((void)free_all(&total), _exit (2));
	}
	result = 0;
	if (its_over(argv[1], &result))
	{
		write_error(argv[1]);
		((void)free_all(&total), _exit (EXIT_FAILURE));
	}
	result = result % 256;
	((void)free_all(&total), _exit(result));
	return (result);
}
