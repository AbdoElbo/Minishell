
#include "minishell.h"

void	char_append(char *temp, char c)
{
	int	size;

	size = ft_strlen(temp);
	printf("\n%i\n", size);
	temp[size] = c;
}

void	is_quote_space(int *j, int *i, t_cmds *cmds, char *temp)
{
	char	*str;
	char	quote;

	str = cmds->whole_cmd;
	if (str[*j] == '\'' || str[*j] == '"')
	{
		quote = (str)[*j];
		temp[(*i)++] = str[(*j)++];
		while (str[*j] != quote)
		{
			temp[(*i)++] = str[(*j)++];
		}
		temp[(*i)++] = str[(*j)++];
	}
	else if (ft_isspace(str[*j]))
	{
		temp[(*i)++] = str[(*j)++];
		while (str[*j] && ft_isspace(str[*j]))
			(*j)++;
	}
}

// static char	**get_envp(t_total_info *total)
// {
// 	t_envp	*temp;
// 	char	**s_envp;
// 	int		i;

// 	i = 0;
// 	temp = total->our_envp;
// 	s_envp = ft_calloc((ft_t_envp_size(total->our_envp) + 1), sizeof(char *));
// 	if (!s_envp)
// 		return (write(2, "Memalloc 1 in expand failed", 30), NULL);
// 	while (temp)
// 	{
// 		s_envp[i] = ft_strdup(temp->string);
// 		if (!s_envp[i])
// 		{
// 			i--;
// 			while (i >= 0)
// 				free(s_envp[i--]);
// 			free(s_envp);
// 			return (write(2, "Memalloc 2 in expand in strdup fail", 34), NULL);
// 		}
// 		i++;
// 		temp = temp->next;
// 	}
// 	return (s_envp);
// }

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

// static int	expand_var()
// {
// 	//iterares until it finds an '"' or '\0' or ' ' and searched our envp to find the value of that var and appends it to cmds[i]
// }
