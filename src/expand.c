
#include "minishell.h"

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

static int	finish_argv(int *arg_index, t_cmds *cmds, char *temp)
{
	char	**temp1;
	int		i;

	*arg_index = *arg_index + 1;
	temp1 = ft_calloc(*arg_index + 1, sizeof(char *));
	i = 0;
	while (cmds->argv && cmds->argv[i])
	{
		temp1[i] = ft_strdup(cmds->argv[i]);
		if (!temp1[i])
			return (free_arr(temp1), 0);
		i++;
	}
	temp1[i] = ft_strdup(temp);
	if (!temp1[i])
		return (free_arr(temp1), 0);
	free_arr(cmds->argv);
	cmds->argv = temp1;
	return (1);
}

static void	char_append(char *temp, char c)
{
	int	size;

	size = ft_strlen(temp);
	printf("\n%i\n", size);
	temp[size] = c;
}

int	increase_temp_size(char **temp, int *size)
{
	char	*new_temp;

	(*size) *= 2;
	new_temp = ft_calloc(*size, sizeof(char));
	if (!new_temp)
		return (0);
	ft_strlcpy(new_temp, *temp, (*size) / 2);
	return (1);
}

static int	expand_one_cmd(t_cmds *cmds, enum e_state state)
{
	char	*str;
	int		arg_index;
	char	*temp;
	int		str_size;
	int		i;

	i = 0;
	arg_index = 0;
	str = cmds->whole_cmd;
	str_size = ft_strlen(str) * 2;
	temp = ft_calloc(str_size, sizeof(char));
	if (!temp)
		return (write(2, "memalloc 2 fail in expand_one_cmd", 33), 0);
	while (str[i])
	{
		if (ft_strlen(temp) == str_size - 2) // the 2 here is a bit random, we just indicate that we are starting to reach the end of the string
		{
			if (!increase_temp_size(&temp, &str_size))
				return (0);
		}
		if (state == NORMAL)
		{
			if (str[i] == '"')
				state = DQUOTE;
			else if (str[i] == '\'')
				state = SQUOTE;
			// else if (str[i] == '$')
			// 	expand_var();
			else if (ft_isspace(str[i]))
			{
				if (!finish_argv(&arg_index, cmds, temp))
					return (free(temp), 0);
				ft_bzero(temp, ft_strlen(temp));
			}
			else if (str[i + 1] == '\0')
			{
				char_append(temp, str[i]);
				if (!finish_argv(&arg_index, cmds, temp))
					return (free(temp), 0);
			}
			else
				char_append(temp, str[i]);
		}
		else if (state == SQUOTE)
		{
			if (str[i] == '\'')
			{
				state = NORMAL;
				if (str[i + 1] == '\0')
					if (!finish_argv(&arg_index, cmds, temp))
						return (free(temp), 0);
			}
			else
				char_append(temp, str[i]);
		}
		else
		{
			if (str[i] == '"')
			{
				state = NORMAL;
				if (str[i + 1] == '\0')
					if (!finish_argv(&arg_index, cmds, temp))
						return (free(temp), 0);
			}
			// else if (str[i] == '$')
			// 	expand_var();
			else
				char_append(temp, str[i]);
		}
		i++;
	}
	return (free(temp), 1);
}

void	is_quote(int *space_c, int *i, t_cmds *cmds, char *temp)
{
	char	*str;

	str = cmds->whole_cmd;
	if ((str)[(*i)] == '\'')
	{
		temp[*i] = str[(*i) + *space_c];
		*i = *i +1;
		while (((str)[*i] != '\''))
		{
			temp[*i] = str[(*i) + *space_c];
			*i = *i +1;
		}
	}
	if ((str)[(*i)] == '"')
	{
		temp[*i] = str[(*i) + *space_c];
		*i = *i +1;
		while (((str)[*i] != '"'))
		{
			temp[*i] = (str)[*i + *space_c];
			*i = *i +1;
		}
	}
	if (ft_isspace((str)[(*i) + *space_c]))
	{
		temp[*i] = (str)[*i + *space_c];
		*i = *i +1;
		*space_c = *space_c + 1;
	}
}

int	fix_whole_command(t_cmds *cmds)
{
	char	*temp;
	int		i;
	int		space_c;
	char	*str;

	str = cmds->whole_cmd;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (free(temp), 0);
	i = 0;
	space_c = 0;
	while ((str)[i + space_c])
	{
		//I NEED TO FIX IT HERE SO IT WONT SKIP THE LAST LETTER OF EACH ARGV FROM THE SECND AND ON.
		if (((str)[i] == '\'') || ((str)[i] == '"') || ft_isspace((str)[i + space_c]))
			is_quote(&space_c, &i, cmds, temp);
		while ((str)[i + space_c] && ft_isspace((str)[i + space_c]))
			space_c++;
		temp[i] = (str)[i + space_c];
		i++;
	}
	free((str));
	str = ft_strdup(temp);
	if (!(str))
		return (free(temp), 0);
	return (free(temp), 1);
}

int	expand(t_total_info *total)
{
	t_cmds			*cmds;
	enum e_state	state;

	cmds = total->cmds;
	while (cmds)
	{
		state = NORMAL;
		if (!fix_whole_command(cmds))
			return (0);
		expand_one_cmd(cmds, state);
		cmds = cmds->next;
	}
	return (1);
}
