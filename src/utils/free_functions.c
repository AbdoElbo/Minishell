/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:14:41 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/13 17:14:44 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_stds(t_total_info *total)
{
	if (!total)
		return (1);
	if (total->stdin != -1)
	{
		if (dup2(total->stdin, STDIN_FILENO) == -1)
			return (perror("Dup2 for STDIN failed"), 1);
		close(total->stdin);
		total->stdin = -1;
	}
	if (total->stdout != -1)
	{
		if (dup2(total->stdout, STDOUT_FILENO) == -1)
			return (perror("Dup2 for STDOUT failed"), 1);
		close(total->stdout);
		total->stdout = -1;
	}
	return (0);
}

void	free_all(t_total_info **total)
{
	int	exit;

	exit = 0;
	if (*total)
		exit = reset_stds(*total);
	if (*total)
	{
		if ((*total)->token)
		{
			ft_token_clear(&(*total)->token);
			(*total)->token = NULL;
		}
		if ((*total)->cmds)
		{
			ft_cmds_clear(&(*total)->cmds);
			(*total)->cmds = NULL;
		}
		if ((*total)->our_envp)
		{
			ft_t_envp_clear(&(*total)->our_envp);
		}
		free(*total);
	}
	if (exit)
		_exit(EXIT_FAILURE);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_data(t_expand *data)
{
	if (data)
	{
		if (data->temp)
			free(data->temp);
		free(data);
	}
}
