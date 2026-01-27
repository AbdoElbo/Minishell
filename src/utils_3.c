
#include "minishell.h"

static t_cmds	*create_newcmds(void)
{
	t_cmds	*new_node;

	new_node = ft_calloc(1, sizeof(t_cmds));
	if (!new_node)
		return (write(2, "Mem aloc 1 in create_newcmd failed", 34), NULL);
	new_node->argv = ft_calloc(2, sizeof(char *));
	if (!new_node->argv)
		return (write(2, "Mem aloc 2 in create_newcmd failed", 34), NULL);
	*new_node->argv = NULL;
	new_node->next = NULL;
	new_node->redir = NULL;
	new_node->whole_cmd = NULL;
	return (new_node);
}

// static int	count_cmds(t_token *lst)
// {
// 	int	i;

// 	i = 1;
// 	if (!lst)
// 		return (0);
// 	while (lst)
// 	{
// 		if (lst->type == PIPE)
// 			i++;
// 		lst = lst->next;
// 	}
// 	return (i);
// }

static int	add_argv(t_cmds *new_node, char *new_argv)
{
	char	*temp;

	temp = ft_strjoin_arg(new_node->whole_cmd, new_argv);
	if (!(temp))
		return (write(2, "str_join in add_argv failed", 27), 0);
	free(new_node->whole_cmd);
	new_node->whole_cmd = ft_strdup(temp);
	free(temp);
	if (!(new_node->whole_cmd))
		return (write(2, "ft_strdup in add_argv failed", 28), 0);
	return (1);
}

int	return_i(char *redir_file)
{
	int	i;

	i = 0;
	while (redir_file[i])
	{
		if (redir_file[i] == '\'')
		{
			i++;
			while (redir_file[i] != '\'')
				i++;
		}
		else if (redir_file[i] == '"')
		{
			i++;
			while (redir_file[i] != '"')
				i++;
		}
		else if (ft_isspace(redir_file[i]))
			break ;
		i++;
	}
	return (i);
}

static int	add_redir(t_token **lst, t_cmds *node, t_type redir_type,
	char *redir_file)
{
	t_redir	*new_redir;
	int		i;

	i = 0;
	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (write(2, "Mem alloc in add_redir calloc failed", 36), 0);
	i = return_i(redir_file);
	new_redir->file = ft_substr(redir_file, 0, i);
	if (!new_redir->file)
		return (write(2, "Mem alloc in add_redir ft_substr failed", 39), 0);
	while (redir_file[i] && ft_isspace(redir_file[i]))
		i++;
	if (!add_argv(node, &redir_file[i]))
		return (write(2, "Mem alloc in add_redir strdup failed", 36), 0);
	new_redir->type = redir_type;
	new_redir->fd = -1;
	ft_redir_addback(&node->redir, new_redir);
	*lst = (*lst)->next;
	return (1);
}

int	add_node(t_cmds **cmds, t_cmds **new_node)
{
	ft_cmds_addback(cmds, *new_node);
	*new_node = create_newcmds();
	if (!*new_node)
		return (0);
	return (1);
}

int	get_cmds(t_total_info *total, t_token *lst)
{
	t_cmds	*new_node;

	new_node = create_newcmds();
	if (!new_node)
		return (0);
	while (lst)
	{
		if (lst->type == WORD)
		{
			if (!add_argv(new_node, lst->value))
				return (0);
		}
		else if (lst->type != WORD && lst->type != PIPE)
		{
			if (!add_redir(&lst, new_node, lst->type, lst->next->value))
				return (0);
		}
		else if (lst->type == PIPE)
		{
			if (!add_node(&total->cmds, &new_node))
				return (0);
		}
		lst = lst->next;
	}
	return (ft_cmds_addback(&total->cmds, new_node), 1);
}
