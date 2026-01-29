
#include "minishell.h"

static void	is_quote_space(int *j_index, int *i_index, t_cmds *cmds, char *temp)
{
	char	*str;
	char	quote;
	int		i;
	int		j;

	i = *i_index;
	j = *j_index;
	str = cmds->whole_cmd;
	if (str[j] == '\'' || str[j] == '"')
	{
		quote = (str)[j];
		temp[i++] = str[j++];
		while (str[j] != quote)
			temp[i++] = str[j++];
		temp[i++] = str[j++];
	}
	else if (ft_isspace(str[j]))
	{
		temp[i++] = str[j++];
		while (str[j] && ft_isspace(str[j]))
			j++;
	}
	*i_index = i;
	*j_index = j;
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
		return (0);
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
	if (temp[ft_strlen(temp) - 1] == ' ')
		temp[ft_strlen(temp) - 1] = '\0';
	cmds->whole_cmd = ft_strdup(temp);
	if (!(cmds->whole_cmd))
		return (free(temp), 0);
	return (free(temp), 1);
}

// static void	is_quote_space_redir(int *j_index, int *i_index, t_cmds *cmds, char *temp)
// {
// 	char	*str;
// 	char	quote;
// 	int		i;
// 	int		j;

// 	i = *i_index;
// 	j = *j_index;
// 	str = cmds->redir->file;
// 	if (str[j] == '\'' || str[j] == '"')
// 	{
// 		quote = (str)[j];
// 		temp[i++] = str[j++];
// 		while (str[j] != quote)
// 			temp[i++] = str[j++];
// 		temp[i++] = str[j++];
// 	}
// 	else if (ft_isspace(str[j]))
// 	{
// 		temp[i++] = str[j++];
// 		while (str[j] && ft_isspace(str[j]))
// 			j++;
// 	}
// 	*i_index = i;
// 	*j_index = j;
// }

// static int	fix_whole_command_redir(t_cmds *cmds)
// {
// 	char	*temp;
// 	int		i;
// 	int		j;
// 	char	*str;

// 	str = cmds->redir->file;
// 	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
// 	if (!temp)
// 		return (0);
// 	i = 0;
// 	j = 0;
// 	while ((str)[j])
// 	{
// 		if ((str[j] == '\'') || (str[j] == '"') || ft_isspace(str[j]))
// 			is_quote_space_redir(&j, &i, cmds, temp);
// 		else
// 			temp[i++] = str[j++];
// 	}
// 	free((cmds->redir->file));
// 	if (temp[ft_strlen(temp) - 1] == ' ')
// 		temp[ft_strlen(temp) - 1] = '\0';
// 	cmds->redir->file = ft_strdup(temp);
// 	if (!(cmds->redir->file))
// 		return (free(temp), 0);
// 	return (free(temp), 1);
// }

static t_expand	*init_data(char *whole_cmds)
{
	t_expand	*data;

	data = ft_calloc(1, sizeof(t_expand));
	if (!data)
		return (write(2, "memalloc 1 fail in init_data", 28), NULL);
	data->state = NORMAL;
	data->i = 0;
	data->i_redir = 0;
	data->arg_index = 0;
	data->str = whole_cmds;
	data->redir_file = NULL;
	data->redir_size = 0;
	data->str_size = ft_strlen(data->str) * 2;
	data->temp = ft_calloc(data->str_size, sizeof(char));
	if (!data->temp)
		return (write(2, "memalloc 2 fail in init_data", 28), free(data), NULL);
	return (data);
}

int	expand(t_total_info *total)
{
	t_cmds			*cmds;
	t_redir			*temp;
	t_expand		*data;

	cmds = total->cmds;
	while (cmds)
	{
		if (!fix_whole_command(cmds))
			return (free_data(data), 0);
		data = init_data(cmds->whole_cmd);
		if (!data)
			return (0);
		expand_one_cmd(total, cmds, data);
		temp = cmds->redir;
		while (cmds->redir)
		{
			data->redir_file = ft_strdup(cmds->redir->file);
			if (!data->redir_file)
				return (write(2, "memaloc in expand fail", 22), 0);
			expand_one_redir(total, cmds, data);
			cmds->redir = cmds->redir->next;
			free(data->redir_file);
		}
		cmds->redir = temp;
		cmds = cmds->next;
		free_data(data);
	}
	return (1);
}
