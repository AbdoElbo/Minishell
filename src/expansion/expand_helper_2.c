
#include "minishell.h"

size_t	count_words(char **a)
{
	size_t	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

void	char_append(char *temp, char c)
{
	int	size;

	size = ft_strlen(temp);
	temp[size] = c;
	temp[size + 1] = '\0';
}

int	increase_buffer(char **temp, int *size, int var_len)
{
	char	*new_temp;

	if (*size > var_len)
		(*size) *= 2;
	else
		(*size) = var_len * 2;
	new_temp = ft_calloc(*size, sizeof(char));
	if (!new_temp)
		return ((write(2, "mem aloc fail in increase_buffer", 32), 0));
	ft_strlcpy(new_temp, *temp, (*size) / 2);
	free(*temp);
	*temp = new_temp;
	return (1);
}

int	finish_argv(int *arg_index, t_cmds *cmds, char *temp)
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
	if (ft_strlen(cmds->whole_cmd))
	{
		temp1[i] = ft_strdup(temp);
		if (!temp1[i])
			return (free_arr(temp1), 0);
		free_arr(cmds->argv);
		cmds->argv = temp1;
	}
	else
		free_arr(temp1);
	cmds->argc = count_words(cmds->argv);
	return (1);
}
