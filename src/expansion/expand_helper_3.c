#include "minishell.h"

static size_t	count_words(char **a)
{
	size_t	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

static int	finish_argv(int *arg_index, t_cmds *cmds, char *temp)
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
	if (!ft_isspace(data->temp[ft_strlen(data->temp) - 1]))
	{
		last_str = ft_strdup(temp[i - 1]);
		if (!last_str)
			return (0);
		free(temp[i - 1]);
		temp[i - 1] = NULL;
	}
	i = 0;
	while (temp[i])
	{
		if (!finish_argv(&data->arg_index, total->cmds, temp[i]))
			return (free(data->temp), free_arr(temp), free(last_str), 0);
		i++;
	}
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
			data->i++; //we added this condition to make sure that when var is null we dont create an argv.
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
		if (ft_strlen(data->temp) == data->str_size - 1) // the 1 here is a bit random, we just indicate that we are starting to reach the end of the string
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
	// if (ft_strlen(data->temp))
	if (!finish_argv(&data->arg_index, cmds, data->temp))
		return (free(data->temp), 0);
	ft_bzero(data->temp, ft_strlen(data->temp)); //not sure if its needed!
	if (!result)
		return (0);
	return (1);
}
