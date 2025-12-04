
#include "minishell.h"

int is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

//DEFINITELY DELETING THEM LATER//
// static int single_quote(char *line, int *i)
// {
//     (*i)++;
//     while (line[*i] && line[*i] != '\'')
// 	{
//     	(*i)++;
// 	}
// 	if (line[*i] != '\'')
// 		return (write(2, "Single quotes open", 18), 0);
//     return (1);
// }
// static int double_quote(char *line, int *i)
// {
//     (*i)++;
//     while (line[*i] && line[*i] != '"')
// 	{
//     	(*i)++;
// 	}
// 	if (line[*i] != '"')
//         return(write(2, "Double quotes open", 18), 0);
//     return (1);
// }

static int quote_handler (char *line, int *i)
{
	if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		if (line[*i] != '"')
			return(write(2, "Double quotes open", 18), 0);
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (line[*i] != '\'')
			return (write(2, "Single quotes open", 18), 0);
	}
	return (1);
}

static int handler(char *line, int *i)
{
    if (line[*i] == '|')  
        return((*i)++, 1);
    else if (line[*i] == '<')
    {
        if (line[(*i) + 1] == '<')
            (*i)+= 2;
        else
            (*i)++;
    }
    else if (line[*i] == '>')
    {
        if (line[(*i) + 1] == '>')
            (*i)+= 2;
        else
            (*i)++;
    }
	return (1);
}

static char *get_next_word (char *line, int *i)
{
	char	*word;
	int		start;

	word = NULL;
	while (ft_isspace(line[*i]))
		(*i)++;
	start = *i;
	if (line[*i] && is_operator(line[*i]))
		{
			handler(line, i);
			word = ft_substr(line, start, *i - start);
				return (word);
		}
	else
	{
		while (line[*i] && !is_operator(line[*i]))
		{
			if (line[*i] == '"' || line[*i] == '\'')
				if (!quote_handler(line, i))
					return (NULL);
			(*i)++;
		}
	}
	if ((i - start) > 0)
		word = ft_substr(line, start, *i - start);
	return (word);
}

t_token *parse_input(char *line)
{
	int		i;
	int		w_count;
	char	*str;
	t_token	*lst;
	t_token	*node;

	i = 0;
	lst = NULL;
	w_count = 0;
	// if (!lst)
	//     return (write(2, "ERROR LST DOESN'T EXIST\n", 24), 0);
	while (line[i])
	{
		//new_node(get_next_word(line, &i));
		// printf("%s\n", get_next_word(line, &i));
		str = get_next_word(line, &i);
		node = new_node(str, ft_strlen(str));
		printf("%i\n", ft_strlen(str));
		if (!node)
			return (write(2, "NEW_NODE failed", 15), NULL);
		ft_lstadd_back_2(&lst, node);
		w_count++;
		free (str);
	}
	print_lst(lst);
	return (lst);
}