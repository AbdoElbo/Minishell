
#include "minishell.h"

t_token	*new_node(char *str, int len)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->value = malloc(len + 1);
	if (!new_node->value)
		return (0);
	ft_strlcpy(new_node->value, str, len + 1);
	if (str[0] == '|')
		new_node->type = PIPE;
	else if (str[0] == '>')
	{
		if (len == 2)
			new_node->type = REDIR_APPEND;
		else
			new_node->type = REDIR_OUT;
	}
	else if (str[0] == '<')
	{
		if (len == 2)
			new_node->type = REDIR_HEREDOC;
		else
			new_node->type = REDIR_IN;
	}
	else
		new_node->type = WORD;
	new_node->next = NULL;
	return (new_node);
}

void	check_our_envp(t_envp *our_envp, char **envp)
{
	int	i;

	i = 0;
	if (!our_envp)
		return ;
	printf("\n");
	while (our_envp)
	{
		if (!strcmp(our_envp->string, envp[i]))
			printf("OK, ");
		else
		{
			printf(".\n");
			printf("%s", our_envp->string);
			printf("\n");
			printf("%s", envp[i]);
			printf(".\n");
		}
		i++;
		our_envp = our_envp->next;
	}
	printf("DONE.\n");
}

void	print_lst(t_token *lst)
{
	if (!lst)
		return ;
	printf("----------------LST---------------------\n");
	while (lst)
	{
		printf("\nstring is : %s\n", lst->value);
		if (lst->type == WORD)
			printf("the type is WORD\n");
		if (lst->type == REDIR_APPEND)
			printf("the type is REDIR_APPEND\n");
		if (lst->type == REDIR_HEREDOC)
			printf("the type is REDIR_HEREDOC\n");
		if (lst->type == REDIR_IN)
			printf("the type is REDIR_IN\n");
		if (lst->type == REDIR_OUT)
			printf("the type is REDIR_OUT\n");
		if (lst->type == PIPE)
			printf("the type is PIPE\n");
		lst = lst->next;
	}
	printf("----------------------------------------\n\n");
}

void	print_cmds(t_cmds *cmds)
{
	int		i;
	int		j;
	int		k;
	t_cmds	*temp;
	t_redir	*temp2;

	temp = cmds;
	i = 0;
	if (!temp)
		return ;
	printf("----------------CMDS---------------------");
	while (temp)
	{
		printf("\nCommand block %i:\n", i + 1);
		k = 0;
		printf("Whole command is:%s.\n", temp->whole_cmd);
		printf("Command %i is :", i + 1);
		if (!temp->argv[k])
			printf("'%s' ", temp->argv[k]);
		while (temp->argv[k])
		{
			printf("'%s' ", temp->argv[k]);
			k++;
		}
		printf("\n");
		j = 0;
		temp2 = temp->redir;
		while (temp2)
		{
			printf("Redir block %i:\n", j + 1);
			if (temp2->type == REDIR_APPEND)
				printf("type: REDIR_APPEND, file:%s\n", temp2->file);
			if (temp2->type == REDIR_HEREDOC)
				printf("type: REDIR_HEREDOC, file:%s\n", temp2->file);
			if (temp2->type == REDIR_IN)
				printf("type: REDIR_IN, file:%s\n", temp2->file);
			if (temp2->type == REDIR_OUT)
				printf("type: REDIR_OUT, file:%s\n", temp2->file);
			printf("fd: %i\n", temp2->fd);
			temp2 = temp2->next;
			j++;
		}
		printf("\n");
		temp = temp->next;
		i++;
	}
	printf("-----------------------------------------\n");
}

int	check_lst_syntax(t_token *lst)
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
	if (!lst->next && lst->value[0] == '\0')
		return (printf("SYNTAX ERROR\n"), 0);
	if (curr_type != WORD)
		return (printf("SYNTAX ERROR\n"), 0);
	return (1);
}
