
#include "minishell.h"

static t_type	*redir_vector(t_token *lst)
{
	
}

static int	count_cmds(t_token *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->type == PIPE)
			i++;
		lst = lst->next;
	}
	return (i);
}

static t_cmds	**init_structs(t_token *lst)
{
	
}

t_cmds	**get_cmds(t_token *lst)
{
	t_cmds	*cmds;
	t_cmds	*new_node;

	new_node = create_newcmds();
	while (lst)
	{
		if (lst->type == WORD)
		{
			add_argv(&new_node->argv, lst->value);
		}
		else if (lst->type != WORD && lst->type != PIPE)
		{
			add_redir(&new_node->redir, lst->type, lst->next->value);
			lst = lst->next;
		}
		else if (lst->type == PIPE)
		{
			ft_lstadd_back(&cmds, new_node);
			new_node = create_newcmds();
		}
		lst = lst->next;
	}
	ft_lstadd_back(&cmds, new_node);
	return (cmds);
}
