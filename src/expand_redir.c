
#include "minishell.h"

static int	normal(t_total_info *total, t_expand *data, t_cmds *cmds, int *i)
{
	(void)cmds;
	if (data->redir_file[*i] == '"')
		data->state = DQUOTE;
	else if (data->redir_file[*i] == '\'')
		data->state = SQUOTE;
	else if (data->redir_file[*i] == '$')
	{
		if (cmds->redir->type == REDIR_HEREDOC)
			char_append(data->temp, '$');
		else
			expand_var_redir(total, data);
	}
	else
		char_append(data->temp, data->redir_file[*i]);
	return (1);
}

static int	squote(t_expand *data, t_cmds *cmds, int *i)
{
	(void)cmds;
	if (data->redir_file[*i] == '\'')
		data->state = NORMAL;
	else
		char_append(data->temp, data->redir_file[*i]);
	return (1);
}

static int	dquote(t_total_info *total, t_expand *data, t_cmds *cmds, int *i)
{
	(void)cmds;
	if (data->redir_file[*i] == '"')
		data->state = NORMAL;
	else if (data->redir_file[*i] == '$')
	{
		if (cmds->redir->type == REDIR_HEREDOC)
			char_append(data->temp, '$');
		else
			expand_var_redir(total, data);
	}
	else
		char_append(data->temp, data->redir_file[*i]);
	return (1);
}

int	expand_one_redir(t_total_info *total, t_cmds *cmds, t_expand *data)
{
	int	result;

	data->redir_size = ft_strlen(data->redir_file) * 2;
	while (data->redir_file[data->i_redir])
	{
		if (ft_strlen(data->temp) == data->redir_size - 1) // the 1 here is a bit random, we just indicate that we are starting to reach the end of the string
			if (!increase_buffer(&data->temp, &data->redir_size, 0))
				return (0);
		if (data->state == NORMAL)
			result = normal(total, data, cmds, &data->i_redir);
		else if (data->state == SQUOTE)
			result = squote(data, cmds, &data->i_redir);
		else
			result = dquote(total, data, cmds, &data->i_redir);
		data->i_redir++;
	}
	free(cmds->redir->file);
	cmds->redir->file = ft_strdup(data->temp);
	if (!cmds->redir->file)
		return (0);
	ft_bzero(data->temp, ft_strlen(data->temp)); //not sure if its needed!
	data->i_redir = 0;
	if (!result)
		return (0);
	return (1);
}
