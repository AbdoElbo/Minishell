
#include "minishell.h"

static int	normal(t_total_info *total, t_expand *data, t_cmds *cmds, int *i)
{
	(void)cmds;
	if (cmds->redir->file[*i] == '"')
		data->state = DQUOTE;
	else if (cmds->redir->file[*i] == '\'')
		data->state = SQUOTE;
	else if (cmds->redir->file[*i] == '$')
	{
		if (cmds->redir->type == REDIR_HEREDOC)
			char_append(data->r_temp, '$');
		else
			if (!expand_var_redir(total, data))
				return (0);
	}
	else
		char_append(data->r_temp, cmds->redir->file[*i]);
	return (1);
}

static int	squote(t_expand *data, t_cmds *cmds, int *i)
{
	(void)cmds;
	if (cmds->redir->file[*i] == '\'')
		data->state = NORMAL;
	else
		char_append(data->r_temp, cmds->redir->file[*i]);
	return (1);
}

static int	dquote(t_total_info *total, t_expand *data, t_cmds *cmds, int *i)
{
	(void)cmds;
	if (cmds->redir->file[*i] == '"')
		data->state = NORMAL;
	else if (cmds->redir->file[*i] == '$')
	{
		if (cmds->redir->type == REDIR_HEREDOC)
			char_append(data->r_temp, '$');
		else
			if (!expand_var_redir(total, data))
				return (0);
	}
	else
		char_append(data->r_temp, cmds->redir->file[*i]);
	return (1);
}

int	expand_one_redir(t_total_info *total, t_cmds *cmds, t_expand *data)
{
	int	result;

	data->redir_size = ft_strlen(data->r_temp) * 2 + 1;
	while (cmds->redir->file[data->i_redir])
	{
		if (ft_strlen(data->r_temp) == data->redir_size - 1) // the 1 here is a bit random, we just indicate that we are starting to reach the end of the string
			if (!increase_buffer(&data->r_temp, &data->redir_size, 0))
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
	cmds->redir->file = ft_strdup(data->r_temp);
	if (!cmds->redir->file)
		return (write(2, "ft-strdup failed in expand_one_redir\n", 37), 0);
	ft_bzero(data->r_temp, ft_strlen(data->r_temp)); //not sure if its needed!
	data->i_redir = 0;
	if (!result)
		return (0);
	return (1);
}
