/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:12:32 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:13:00 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_words(char **a)
{
	size_t	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

int	finish_argv(int *arg_index, t_cmds *cmds, char *temp)
{
	char	**temp1;
	int		i;

	*arg_index = *arg_index + 1;
	temp1 = ft_calloc(*arg_index + 1, sizeof(char *));
	i = 0;
	while (cmds->argv && cmds->argv[i])
	{
		temp1[i] = ft_strdup(cmds->argv[i]);
		if (!temp1[i])
			return (free_arr(temp1), 0);
		i++;
	}
	if (ft_strlen(cmds->whole_cmd))
	{
		temp1[i] = ft_strdup(temp);
		if (!temp1[i])
			return (free_arr(temp1), 0);
		free_arr(cmds->argv);
		cmds->argv = temp1;
	}
	else
		free_arr(temp1);
	cmds->argc = count_words(cmds->argv);
	return (1);
}

int	split_handle_isspace(char **last_str, t_expand *data,
	char **temp, int i)
{
	if (!ft_isspace(data->temp[ft_strlen(data->temp) - 1]))
	{
		*last_str = ft_strdup(temp[i - 1]);
		if (!*last_str)
			return (0);
		free(temp[i - 1]);
		temp[i - 1] = NULL;
	}
	return (1);
}
