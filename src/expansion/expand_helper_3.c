/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:45:32 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:12:51 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_command(t_total_info *total, t_expand *data)
{
	char	**temp;
	char	*last_str;
	int		i;

	i = 0;
	last_str = NULL;
	while (data->temp[i] && !ft_isspace(data->temp[i]))
		i++;
	if (!data->temp[i])
		return (1);
	temp = ft_split(data->temp, ' ');
	i = 0;
	while (temp[i])
		i++;
	if (!split_handle_isspace(&last_str, data, temp, i))
		return (free_arr(temp), free(last_str), 0);
	i = 0;
	while (temp[i])
		if (!finish_argv(&data->arg_index, total->cmds, temp[i++]))
			return (free(data->temp), free_arr(temp), free(last_str), 0);
	ft_bzero(data->temp, ft_strlen(data->temp));
	if (last_str && ft_strlen(last_str) > 0)
		ft_memcpy(data->temp, last_str, ft_strlen(last_str));
	return (free_arr(temp), free(last_str), 1);
}

static int	normal(t_total_info *total, t_expand *data, t_cmds *cmds)
{
	if (data->str[data->i] == '"')
		data->state = DQUOTE;
	else if (cmds->whole_cmd[data->i] == '\'')
		data->state = SQUOTE;
	else if (cmds->whole_cmd[data->i] == '$')
	{
		expand_var(total, data);
		if (!split_command(total, data))
			return (free(data->temp), 0);
		if (!ft_strlen(data->temp) && ft_isspace(data->str[data->i + 1]))
			data->i++;
	}
	else if (ft_isspace(cmds->whole_cmd[data->i]) && ft_strlen(data->temp))
	{
		if (!finish_argv(&data->arg_index, cmds, data->temp))
			return (free(data->temp), 0);
		ft_bzero(data->temp, ft_strlen(data->temp));
	}
	else
		char_append(data->temp, cmds->whole_cmd[data->i]);
	return (1);
}

static int	squote(t_expand *data, t_cmds *cmds)
{
	(void)cmds;
	if (data->str[data->i] == '\'')
		data->state = NORMAL;
	else
		char_append(data->temp, data->str[data->i]);
	return (1);
}

static int	dquote(t_total_info *total, t_expand *data, t_cmds *cmds)
{
	(void)cmds;
	if (data->str[data->i] == '"')
		data->state = NORMAL;
	else if (data->str[data->i] == '$')
		expand_var(total, data);
	else
		char_append(data->temp, data->str[data->i]);
	return (1);
}

int	expand_one_cmd(t_total_info *total, t_cmds *cmds, t_expand *data)
{
	int	result;

	while (data->str[data->i])
	{
		if (ft_strlen(data->temp) == data->str_size - 1)
			if (!increase_buffer(&data->temp, &data->str_size, 0))
				return (0);
		if (data->state == NORMAL)
			result = normal(total, data, cmds);
		else if (data->state == SQUOTE)
			result = squote(data, cmds);
		else
			result = dquote(total, data, cmds);
		data->i++;
	}
	if (!finish_argv(&data->arg_index, cmds, data->temp))
		return (free(data->temp), 0);
	ft_bzero(data->temp, ft_strlen(data->temp));
	if (!result)
		return (0);
	return (1);
}
