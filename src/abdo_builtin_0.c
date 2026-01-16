

#include "abdo.h"

static int	get_identifier_and_value(char *str, char **identifier,
				char **value, int *has_value)
{
	int	i;

	i = 0;
	*identifier = NULL;
	*value = NULL;
	*has_value = 0;
	while (str[i] && str[i] != '=')
		i++;
	*identifier = ft_substr(str, 0, i);
	if (!*identifier)
		return (0);
	if (str[i] == '=')
	{
		*has_value = 1;
		*value = ft_strdup(str + i + 1);
		if (!*value)
			return (free(*identifier), 0);
	}
	else
	{
		*has_value = 0;
		*value = NULL;
	}
	return (1);
}

int	update_env(t_env **env)
{
	t_env	*temp;
	char	*identifier;
	char	*value;
	int		has_value;

	temp = *env;
	while (temp)
	{
		identifier = NULL;
		value = NULL;
		has_value = 0;
		if (!get_identifier_and_value(temp->string, &identifier
				, &value, &has_value))
			return (free(identifier), free(value), EXIT_FAILURE);
		temp->identifier = identifier;
		temp->value = value;
		temp->has_value = has_value;
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
