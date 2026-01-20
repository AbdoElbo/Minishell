
#include "minishell.h"

// static int	expand_var()
// {

// }

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
	temp1[i] = ft_strdup(temp);
	if (!temp1[i])
		return (free_arr(temp1), 0);
	free_arr(cmds->argv);
	cmds->argv = temp1;
	return (1);
}

int	normal(t_expand *token, t_cmds *cmds)
{
	if (token->str[token->i] == '"')
		token->state = DQUOTE;
	else if (cmds->whole_cmd[token->i] == '\'')
		token->state = SQUOTE;
	// else if (str[i] == '$')
	// 	expand_var();
	else if (ft_isspace(cmds->whole_cmd[token->i]))
	{
		if (!finish_argv(&token->arg_index, cmds, token->temp))
			return (free(token->temp), 0);
		ft_bzero(token->temp, ft_strlen(token->temp));
	}
	else if (cmds->whole_cmd[token->i + 1] == '\0')
	{
		char_append(token->temp, cmds->whole_cmd[token->i]);
		if (!finish_argv(&token->arg_index, cmds, token->temp))
			return (free(token->temp), 0);
	}
	else
		char_append(token->temp, cmds->whole_cmd[token->i]);
	return (1);
}

int	squote(t_expand *data, t_cmds *cmds)
{
	if (data->str[data->i] == '\'')
	{
		data->state = NORMAL;
		if (data->str[data->i + 1] == '\0')
			if (!finish_argv(&data->arg_index, cmds, data->temp))
				return (free(data->temp), 0);
	}
	else
		char_append(data->temp, data->str[data->i]);
	return (1);
}

int	dquote(t_expand *data, t_cmds *cmds)
{
	if (data->str[data->i] == '"')
	{
		data->state = NORMAL;
		if (data->str[data->i + 1] == '\0')
			if (!finish_argv(&data->arg_index, cmds, data->temp))
				return (free(data->temp), 0);
	}
	// else if (str[i] == '$')
	// 	expand_var();
	else
		char_append(data->temp, data->str[data->i]);
	return (1);
}
