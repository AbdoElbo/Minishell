
#include "minishell.h"

static int	increase_buffer(char **temp, int *size)
{
	char	*new_temp;

	(*size) *= 2;
	new_temp = ft_calloc(*size, sizeof(char));
	if (!new_temp)
		return (0);
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
			is_quote_space(&j, &i, cmds, temp);
		else
			temp[i++] = str[j++];
	}
	free((cmds->whole_cmd));
	cmds->whole_cmd = ft_strdup(temp);
	if (!(cmds->whole_cmd))
		return (free(temp), 0);
	return (free(temp), 1);
}

static t_expand	*init_data(t_state state, char *whole_cmds)
{
	t_expand	*data;

	data = ft_calloc(1, sizeof(t_expand));
	if (!data)
		return (NULL);
	data->state = state;
	data->i = 0;
	data->arg_index = 0;
	data->str = whole_cmds;
	data->str_size = ft_strlen(data->str) * 2;
	data->temp = ft_calloc(data->str_size, sizeof(char));
	if (!data->temp)
		return (free(data), NULL);
	return (data);
}

static int	expand_one_cmd(t_cmds *cmds, t_state state)
{
	t_expand	*data;
	int			result;

	data = init_data(state, cmds->whole_cmd);
	if (!data)
		return (write(2, "memalloc 2 fail in expand_one_cmd", 33), 0);
	while (data->str[data->i])
	{
		if (ft_strlen(data->temp) == data->str_size - 1) // the 1 here is a bit random, we just indicate that we are starting to reach the end of the string
			if (!increase_buffer(&data->temp, &data->str_size))
				return (0);
		if (state == NORMAL)
			result = normal(data, cmds);
		else if (state == SQUOTE)
			result = squote(data, cmds);
		else
			result = dquote(data, cmds);
		data->i++;
	}
	if (!result)
		return (free_data(data), 0);
	return (free_data(data), 1);
}

int	expand(t_total_info *total)
{
	t_cmds			*cmds;
	enum e_state	state;

	cmds = total->cmds;
	while (cmds)
	{
		state = NORMAL;
		if (!fix_whole_command(cmds))
			return (0);
		expand_one_cmd(cmds, state);
		cmds = cmds->next;
	}
	return (1);
}

// static int	expand_one_cmd(t_cmds *cmds, enum e_state state)
// {
// 	char		*str;
// 	int			arg_index;
// 	char		*temp;
// 	int			str_size;
// 	int			i;

// 	i = 0;
// 	arg_index = 0;
// 	str = cmds->whole_cmd;
// 	str_size = ft_strlen(str) * 2;
// 	temp = ft_calloc(str_size, sizeof(char));
// 	if (!temp)
// 		return (write(2, "memalloc 2 fail in expand_one_cmd", 33), 0);
// 	while (str[i])
// 	{
// 		if (ft_strlen(temp) == str_size - 2) // the 2 here is a bit random, we just indicate that we are starting to reach the end of the string
// 			if (!increase_temp_size(&temp, &str_size))
// 				return (0);
// 		if (state == NORMAL)
// 		{
// 			if (str[i] == '"')
// 				state = DQUOTE;
// 			else if (str[i] == '\'')
// 				state = SQUOTE;
// 			// else if (str[i] == '$')
// 			// 	expand_var();
// 			else if (ft_isspace(str[i]))
// 			{
// 				if (!finish_argv(&arg_index, cmds, temp))
// 					return (free(temp), 0);
// 				ft_bzero(temp, ft_strlen(temp));
// 			}
// 			else if (str[i + 1] == '\0')
// 			{
// 				char_append(temp, str[i]);
// 				if (!finish_argv(&arg_index, cmds, temp))
// 					return (free(temp), 0);
// 			}
// 			else
// 				char_append(temp, str[i]);
// 		}
// 		else if (state == SQUOTE)
// 		{
// 			if (str[i] == '\'')
// 			{
// 				state = NORMAL;
// 				if (str[i + 1] == '\0')
// 					if (!finish_argv(&arg_index, cmds, temp))
// 						return (free(temp), 0);
// 			}
// 			else
// 				char_append(temp, str[i]);
// 		}
// 		else
// 		{
// 			if (str[i] == '"')
// 			{
// 				state = NORMAL;
// 				if (str[i + 1] == '\0')
// 					if (!finish_argv(&arg_index, cmds, temp))
// 						return (free(temp), 0);
// 			}
// 			// else if (str[i] == '$')
// 			// 	expand_var();
// 			else
// 				char_append(temp, str[i]);
// 		}
// 		i++;
// 	}
// 	return (free(temp), 1);
// }
