/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:39:57 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:40:01 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env_size(t_envp *env)
{
	int		i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**change_to_arr(t_envp *env)
{
	char	**arr;
	int		size;
	int		i;

	if (!env)
		return (NULL);
	size = env_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = ft_strdup(env->string);
		if (!arr[i])
			return (free_arr(arr), NULL);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	word_count(char const *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((!ft_isspace(s[i])) && (i == 0 || ft_isspace(s[i - 1])))
			words++;
		i++;
	}
	return (words);
}
