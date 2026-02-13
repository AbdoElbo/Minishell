/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:15:28 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/13 17:22:43 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_lst_syntax(t_token *lst)
{
	t_type	curr_type;
	t_type	next_type;
	t_token	*tmp;

	if (lst->type == PIPE)
		return (write(2, "Syntax Error\n", 13), 0);
	while (lst->next)
	{
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
		lst = lst->next;
	}
	if (lst->value[0] == '\0')
		return (write(2, "Syntax Error:\nNo redirection File\n", 35), 0);
	if (lst->type != WORD)
		return (write(2, "Syntax Error:\nNo redirection File\n", 35), 0);
	return (1);
}

static int	quote_handler(char *line, int *i)
{
	if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		if (line[*i] != '"')
			return (write(2, "Double quotes open", 18), 0);
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

static int	operator_handler(char *line, int *i)
{
	if (line[*i] == '|')
		return ((*i)++, 1);
	else if (line[*i] == '<')
	{
		if (line[(*i) + 1] == '<')
			(*i) += 2;
		else
			(*i)++;
	}
	else if (line[*i] == '>')
	{
		if (line[(*i) + 1] == '>')
			(*i) += 2;
		else
			(*i)++;
	}
	return (1);
}

static char	*get_next_word(char *line, int *i)
{
	char	*word;
	int		start;

	word = NULL;
	while (ft_isspace(line[*i]))
		(*i)++;
	start = *i;
	if (line[*i] && is_operator(line[*i]))
		operator_handler(line, i);
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
	if (((*i) - start) > 0)
		word = ft_substr(line, start, *i - start);
	return (word);
}

t_token	*parse_input(char *line)
{
	int		i;
	int		w_count;
	char	*str;
	t_token	*lst;
	t_token	*node;

	i = 0;
	lst = NULL;
	w_count = 0;
	while (line[i])
	{
		str = get_next_word(line, &i);
		if (!str)
			return (ft_token_clear(&lst), NULL);
		node = new_node(str, ft_strlen(str));
		free (str);
		if (!node)
			return (write(2, "NEW_NODE failed", 15),
				ft_token_clear(&lst), NULL);
		ft_token_addback(&lst, node);
		w_count++;
	}
	if (!check_lst_syntax(lst))
		return (NULL);
	return (lst);
}
