
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
