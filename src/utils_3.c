
#include "minishell.h"

static t_cmds	*create_newcmds(void)
{
	t_cmds *new_node;

	new_node = ft_calloc(1, sizeof(t_cmds *));
	if (!new_node)
		return (write(2, "Mem aloc for new node in create new cmd failed", 47), NULL);
	new_node->argv = ft_calloc(1, sizeof(char **));
	if (!new_node->argv)
		return (write(2, "Mem aloc for node->argv in create new cmd failed", 48), NULL);
	*new_node->argv = NULL;
	new_node->next = NULL;
	new_node->redir = NULL;
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

static int	add_argv(char **node_argv, char *new_argv)
{
	char    *temp;

	temp = node_argv[0];
	node_argv[0] = ft_strjoin(node_argv[0], new_argv);
	free(temp);
	if (!node_argv[0])
		return (write(2, "str_join in add_argv failed", 27), 0);
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
			break;
		i++;
	}
	return (i);
}

static int	add_redir(t_redir **redir, t_type redir_type, char *redir_file, char **node_argv)
{
	t_redir *new_redir;
	int     i;

	i = 0;
	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (write(2, "Mem alloc in add_redir calloc failed", 36), 0);
	i = return_i(redir_file);
	new_redir->file = ft_substr(redir_file, 0, i);
	if (!new_redir)
		return (write(2, "Mem alloc in add_redir ft_substr failed", 39), 0);
	while (redir_file[i] && ft_isspace(redir_file[i]))
		i++;
	if (!add_argv(node_argv, &redir_file[i]))
		return (write(2, "Mem alloc in add_redir strdup failed", 36), 0);
	new_redir->type = redir_type;
	ft_redir_addback(redir, new_redir);
	return (1);
}

t_cmds	*get_cmds(t_token *lst)
{
	t_cmds	*cmds;
	t_cmds	*new_node;

	cmds = NULL;
	new_node = create_newcmds();
	if (!new_node)
		return (NULL);
	while (lst)
	{
		if (lst->type == WORD)
		{
			if (!add_argv(new_node->argv, lst->value))
				return (NULL); //free everything with total free function.
		}
		else if (lst->type != WORD && lst->type != PIPE)
		{
			if (!add_redir(&new_node->redir, lst->type, lst->next->value, new_node->argv))
				return (NULL); //free everything with total free function.
			
			lst = lst->next;
		}
		else if (lst->type == PIPE)
		{
			ft_cmds_addback(&cmds, new_node);
			new_node = create_newcmds();
			if (!new_node)
				return (NULL); //free everything with total free function.
		}
		lst = lst->next;
	}
	ft_cmds_addback(&cmds, new_node);
	return (cmds);
}
