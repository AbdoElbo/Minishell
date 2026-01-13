
#include "minishell.h"

static int	copy_envp(t_total_info *total, char **envp)
{
	int	i;

	(void)total;
	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	total->our_envp = ft_calloc(i + 1, sizeof(char *));
	if (!total->our_envp)
		return (write(2, "Mem alloc in expand failed", 26), 0);
	i = 0;
	while (envp[i])
	{
		total->our_envp[i] = ft_strdup(envp[i]);
		if (!(total->our_envp[i]))
			return (write(2, "Mem alloc in expand in strdup fail", 34), 0);
		i++;
	}
	return (1);
}

// static int	find_parameter(const char *s1, const char *s2, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] || s2[i]) && i < size)
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	if ((unsigned char)s1[i] != '=')
// 		return (1);
// 	return (0);
// }

// static int	handle_d_quote(char **string)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*new_string;

// 	i = 0;
// 	j = 0;
// 	while ((*string)[i + j])
// 	{
// 		j = 0;
// 		if ((*string)[i + j] != '$')
// 			while (!isspace((*string)[i + j]))
// 				j++;
// 		if (j > 0)
// 		{
// 			find_parameter(total);
// 		}
// 	}
// 	len = ft_strlen(*string) - 2;
// 	new_string = ft_calloc(len + 1, sizeof(char));
// 	if (!new_string)
// 		return (0);
// 	free((*string));
// 	(*string) = new_string;
// 	return (1);
// }

static int	handle_s_quote(char **string)
{
	int		i;
	int		j;
	int		len;
	char	*new_string;

	i = 0;
	j = 0;
	len = ft_strlen(*string) - 2;
	new_string = ft_calloc(len + 1, sizeof(char));
	if (!new_string)
		return (0);
	i = 0;
	while ((*string)[i + j])
	{
		if ((*string)[i + j] != '\'')
		{
			new_string[i] = (*string)[i + j];
			i++;
		}
		else
			j++;
	}
	free((*string));
	(*string) = new_string;
	return (1);
}

static int	find_quotes(t_token *lst)
{
	int		i;
	t_token	*list;

	list = lst;
	i = 0;
	if (list && list->type == WORD)
	{
		while (list->value[i])
		{
		// 	if (list->value[i] == '"')
		// 	{
		// 		if (!handle_d_quote(&(list->value)))
		// 			return (0);
		// 		return (1);
		// 	}
			if (list->value[i] == '\'')
			{
				if (!handle_s_quote(&(list->value)))
					return (0);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	expand(t_total_info *total, char **envp)
{
	t_token	*lst;

	lst = total->token;
	if (!copy_envp(total, envp))
		return (0);
	while (total->cmds)
	{
		while (find_quotes(lst))
			;
		lst = lst->next;
	}
	return (1);
}
