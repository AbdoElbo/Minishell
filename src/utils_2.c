
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

void	print_lst(t_token *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("\nstring is : %s\n", lst->value);
		printf("the tpe is %u\n", lst->type);
		lst = lst->next;
	}
}

void	print_cmds(t_cmds *lst)
{
	int i;
	int j;

	i = 0;
	if (!lst)
		return ;
	while (lst)
	{
		printf("\nCommand block %i:\n", i);
		printf("Command is : %s\n", lst->argv[0]);
		j = 0;
		while (lst->redir)
		{
			printf("Redir block %i:\n", j);
			printf("type: %u, file: %s\n", lst->redir->type, lst->redir->file);
			lst->redir = lst->redir->next;
		}
		printf("\n");
		lst = lst->next;
		i++;
	}
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
	return (1);
}
