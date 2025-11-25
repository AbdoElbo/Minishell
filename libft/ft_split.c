/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:34:55 by hariskon          #+#    #+#             */
/*   Updated: 2025/11/10 13:25:50 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static void		*free_function(char **s, size_t index);
static size_t	count_words(const char *a, char s);

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	word;
	char	**result;

	i = 0;
	word = 0;
	if (s == NULL)
		return (NULL);
	result = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
			result[word++] = ft_substr(s, start, i - start);
		if ((int)(word - 1) >= 0 && result[word - 1] == NULL)
			return (free_function(result, word - 2));
	}
	return (result);
}

static size_t	count_words(const char *a, char s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (a[i])
	{
		while (a[i] == s)
			i++;
		if (a[i])
		{
			count++;
			while (a[i] && a[i] != s)
				i++;
		}
	}
	return (count);
}

static void	*free_function(char **s, size_t index)
{
	int	i;

	i = index;
	while (i >= 0)
		free(s[i--]);
	free (s);
	return (NULL);
}
