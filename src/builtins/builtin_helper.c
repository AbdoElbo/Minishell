/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:40:04 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:40:07 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	get_identifier_and_value(char *str, char **identifier,
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

int	update_env(t_envp **env)
{
	t_envp	*temp;
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
		temp->exported = 1;
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

t_envp	*find_env(t_envp *env, char *identifier)
{
	int	len;

	len = ft_strlen(identifier);
	while (env)
	{
		if (ft_strncmp(env->identifier, identifier, len) == 0
			&& env->identifier[len] == '\0')
			return (env);
		env = env->next;
	}
	return (NULL);
}
