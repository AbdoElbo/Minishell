
#include "minishell.h"

static int	treat_invalid_variable(t_total_info *total, t_expand *data)
{
	char	*exit_code;

	if (data->str[data->i + 1] == '?')
	{
		exit_code = ft_itoa(total->exit_code);
		if (!exit_code)
			return (write(2, "mem aloc fail in expand_var", 27), 0);
		if (ft_strlen(data->temp) + ft_strlen(exit_code) >= data->str_size)
		{
			if (!increase_buffer(&data->temp, &data->str_size))
				return (free(exit_code), 0);
		}
		ft_memcpy(data->temp, exit_code, ft_strlen(exit_code));
		data->i += 1;
		free(exit_code);
	}
	else if (data->str[data->i + 1] == '\0' || ft_isspace(data->str[data->i + 1]))
	{
		ft_memcpy(data->temp + ft_strlen(data->temp), "$", 1);
		printf("%s\n", data->temp);
	}
	else
		data->i += 1;
	return (1);
}

//need to fix the issues with "$" $? "$?" and a lot more.
static int	expand_var(t_total_info *total, t_expand *data)
{
	int		var_len;

	if (!(ft_isalpha(data->str[data->i + 1]) || data->str[data->i + 1] == '_' ))
	{
		if (!treat_invalid_variable(total, data))
			return (0);
	}
	else
	{
		var_len = 0;
		data->i++;
		while ((ft_isalnum(data->str[data->i]) || data->str[data->i] == '_' ))
		{
			ft_strlcat(data->temp, &data->str[data->i], 1);
			data->i++;
			var_len++;
			if (ft_strlen(data->temp) + var_len)
			{
				if (!increase_buffer(&data->temp, &data->str_size))
					return (0);
			}
		}
	}
	return (1);
}

// static int	expand_var(t_total_info *total, t_expand *data, t_cmds *cmds)
// {
// 	char	*var;
// 	int		var_len;
// 	char	*exit_code;

// 	if (data->str[data->i + 1] == '?')
// 	{
// 		exit_code = ft_itoa(total->exit_code);
// 		if (!exit_code)
// 			return (write(2, "mem aloc fail in expand_var", 27), 0);
// 		if (ft_strlen(data->temp) + ft_strlen(exit_code) >= data->str_size)
// 		{
// 			if (!increase_buffer(&data->temp, data->str_size))
// 				return (free(exit_code), 0);
// 		}
// 		ft_strlcat(data->temp, exit_code, ft_strlen(exit_code));
// 		data->i += 2;
// 		free(exit_code);
// 	}
// 	else if (data->str[data->i + 1] == '\0' || ft_isspace(data->str[data->i + 1]))
// 	{
// 		ft_strlcat(data->temp, "$", 1);
// 		data->i += 1;
// 	}
// 	else if (!(is_valid_identifier(data->str[data->i + 1])))
// 		data->i += 2;
// }

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
	temp1[i] = ft_strdup(temp);
	if (!temp1[i])
		return (free_arr(temp1), 0);
	free_arr(cmds->argv);
	cmds->argv = temp1;
	return (1);
}

int	normal(t_total_info *total, t_expand *data, t_cmds *cmds)
{
	if (data->str[data->i] == '"')
		data->state = DQUOTE;
	else if (cmds->whole_cmd[data->i] == '\'')
		data->state = SQUOTE;
	else if (cmds->whole_cmd[data->i] == '$')
		expand_var(total, data);
	else if (ft_isspace(cmds->whole_cmd[data->i]))
	{
		printf("im in\n");
		if (!finish_argv(&data->arg_index, cmds, data->temp))
			return (free(data->temp), 0);
		ft_bzero(data->temp, ft_strlen(data->temp));
	}
	else
		char_append(data->temp, cmds->whole_cmd[data->i]);
	return (1);
}

int	squote(t_expand *data, t_cmds *cmds)
{
	(void)cmds;
	if (data->str[data->i] == '\'')
		data->state = NORMAL;
	else
		char_append(data->temp, data->str[data->i]);
	return (1);
}

int	dquote(t_total_info *total, t_expand *data, t_cmds *cmds)
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
