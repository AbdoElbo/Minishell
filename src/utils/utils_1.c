#include "minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static void	get_type(t_token *new_node, char *str, int len)
{
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
}

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
	get_type(new_node, str, len);
	new_node->next = NULL;
	return (new_node);
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

int	check_lst_type(t_token *lst)
{
	t_type	curr_type;
	t_type	next_type;
	t_token	*tmp;

	curr_type = lst->type;
	next_type = lst->next->type;
	if (curr_type == next_type)
		return (write(2, "Syntax Error\n", 13), 0);
	else if (curr_type == REDIR_OUT && next_type == REDIR_IN)
		return (write(2, "Syntax Error\n", 13), 0);
	else if (curr_type == REDIR_IN && next_type == REDIR_OUT)
		return (write(2, "Syntax Error\n", 13), 0);
	else if (curr_type == REDIR_OUT && next_type == PIPE)
	{
		tmp = lst->next->next;
		ft_token_delone(lst->next);
		lst->next = tmp;
	}
	else if ((curr_type != WORD && curr_type != PIPE) && next_type != WORD)
		return (write(2, "Syntax Error\n", 13), 0);
	return (1);
}
