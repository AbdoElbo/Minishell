
#include "minishell.h"

static t_type *redir_vector(t_token *lst)
{
    t_token *start;
    int     i;
    t_type  *types;

    i = 1;
    start = lst;
    while (lst && lst->type != PIPE)
    {
        if (lst->type != WORD)
            i++;
        lst = lst->next;
    }
    types = ft_calloc(i, sizeof(t_type *));
    if (!types)
        return (write(3, "Mem alloc in redir_vectro failed", 32), NULL);
    i = 0;
    while (start && lst->type != PIPE)
    {
        if (lst->type != WORD)
        {
            types[i] = start->type;
            i++;
        }
        start = start->next;
    }
    return (types);
}

static int	count_cmds(t_token *lst)
{
	int i;
	i = 1;

	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->type == PIPE)
			i++;
		lst = lst->next;
	}
	i++;
	return (i);
}

static t_cmds	**init_structs(t_token *lst)
{
	t_cmds	**cmds;
	int		cmd_count;
	int		i;

	i = 0;
	cmd_count = count_cmds(lst);
	cmds = ft_calloc(cmd_count + 1, sizeof(t_cmds *));
    if (!cmds)
		return (write(2, "Mem alloc in init structs failed", 32), NULL);
	while (i < cmd_count)
	{
		cmds[i] = ft_calloc(1, sizeof(t_cmds *));
		if (!cmds[i])
			return (write(2, "1st Mem alloc in init structs failed", 36), NULL); //free the cmds **
        cmds[i]->cmd = ft_calloc(1, sizeof(char **));
        cmds[i]->redir_file = ft_calloc(1, sizeof(char **));
        cmds[i]->type = ft_calloc(1, sizeof(int));
        if ( !cmds[i]->cmd || !cmds[i]->redir_file || !cmds[i]->type)
            return (write(2, "2nd Mem alloc in init structs failed", 36), NULL);
		i++;
	}
	return (cmds);
}

t_cmds	**get_cmds(t_token *lst)
{
	t_cmds	**cmds;
	int 	i;

	i = 0;
	cmds = init_structs(lst);
	if (!cmds)
		return (NULL); //free struct.
	while (lst)
	{			
		printf("%i\n", i);
        while (lst && lst->type != PIPE)
        {
            cmds[i]->type = redir_vector(lst);
            //CHECKPOINT !!!
            // ADD THE SAME THIS AS THE LINE ABOVE FOR (INFILES/ OUTFILES)
            // AND WE NEED TO CREATE A SUBSTR TO GET THE THE STRING AFTER THE "INFILE"
            // WHICH WILL BE THE BINARY 
        }
        if (lst && lst->type == PIPE)
        {
            i++;
            lst = lst->next;
        }
    }
	i = 0;
	while (cmds[i])
		printf("cmd: %s\n", cmds[i++]->cmd[0]);
	return (cmds);
}

int		check_lst_syntax(t_token *lst)
{
	t_type	prev_type;
	t_type	curr_type;
	while (lst->next)
	{
		prev_type = lst->type;
		curr_type = lst->next->type;
		if (curr_type == prev_type)
			return (printf("SYNTAX ERROR\n"), 0);
		else if (prev_type == REDIR_OUT && curr_type == REDIR_IN)
			return (printf("SYNTAX ERROR\n"), 0);
		else if (prev_type == REDIR_IN && curr_type == REDIR_OUT)
			return (printf("SYNTAX ERROR\n"), 0);
		lst = lst->next;
	}
	return (1);
}