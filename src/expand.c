
#include "minishell.h"

int	increase_buffer(char **temp, int *size)
{
	char	*new_temp;

	(*size) *= 2;
	new_temp = ft_calloc(*size, sizeof(char));
	if (!new_temp)
		return ((write(2, "mem aloc fail in increase_buffer", 32), 0));
	ft_strlcpy(new_temp, *temp, (*size) / 2);
	return (1);
}

static int	fix_whole_command(t_cmds *cmds)
{
	char	*temp;
	int		i;
	int		j;
	char	*str;

	str = cmds->whole_cmd;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (free(temp), 0);
	i = 0;
	j = 0;
	while ((str)[j])
	{
		if ((str[j] == '\'') || (str[j] == '"') || ft_isspace(str[j]))
		{
			is_quote_space(&j, &i, cmds, temp);
		}
		else
			temp[i++] = str[j++];
	}
	free((cmds->whole_cmd));
	if (temp[ft_strlen(temp) - 1] == ' ')
		temp[ft_strlen(temp) - 1] = '\0';
	cmds->whole_cmd = ft_strdup(temp);
	if (!(cmds->whole_cmd))
		return (free(temp), 0);
	return (free(temp), 1);
}

static t_expand	*init_data(char *whole_cmds)
{
	t_expand	*data;

	data = ft_calloc(1, sizeof(t_expand));
	if (!data)
		return (write(2, "memalloc 1 fail in init_data", 28), NULL);
	data->state = NORMAL;
	data->i = 0;
	data->arg_index = 0;
	data->str = whole_cmds;
	data->str_size = ft_strlen(data->str) * 2;
	data->temp = ft_calloc(data->str_size, sizeof(char));
	if (!data->temp)
		return (write(2, "memalloc 2 fail in init_data", 28), free(data), NULL);
	return (data);
}

static int	expand_one_cmd(t_total_info *total, t_cmds *cmds, t_expand *data)
{
	int			result;

	while (data->str[data->i])
	{
		if (ft_strlen(data->temp) == data->str_size - 1) // the 1 here is a bit random, we just indicate that we are starting to reach the end of the string
			if (!increase_buffer(&data->temp, &data->str_size))
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
	ft_bzero(data->temp, ft_strlen(data->temp)); //not sure if its needed!
	if (!result)
		return (0);
	return (1);
}

int	expand(t_total_info *total)
{
	t_cmds			*cmds;
	t_expand		*data;

	cmds = total->cmds;
	while (cmds)
	{
		data = init_data(cmds->whole_cmd);
		if (!data)
			return (free_data(data), 0);
		if (!fix_whole_command(cmds))
			return (free_data(data), 0);
		expand_one_cmd(total, cmds, data);
		cmds = cmds->next;
	}
	return (free_data(data), 1);
}
