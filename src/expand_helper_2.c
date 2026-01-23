
#include "minishell.h"

void	char_append(char *temp, char c)
{
	int	size;

	size = ft_strlen(temp);
	temp[size] = c;
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
