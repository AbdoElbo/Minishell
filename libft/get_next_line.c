/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:35:53 by hariskon          #+#    #+#             */
/*   Updated: 2025/11/10 13:36:31 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin_free(char *s1, char *s2)
{
	char	*new_string;
	char	*old_saved;
	size_t	total_len;
	size_t	i;

	i = 0;
	old_saved = s1;
	total_len = ft_strlen(s1) + ft_strlen(s2) +1;
	new_string = malloc(total_len);
	if (new_string == NULL)
		return (free(old_saved), NULL);
	while (*s1)
		new_string[i++] = *(s1++);
	while (*s2)
		new_string[i++] = *(s2++);
	new_string[i] = '\0';
	return (free(old_saved), new_string);
}

char	*read_until_break(char *saved, int fd)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(saved), NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(saved), NULL);
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
			saved = gnl_strjoin_free(saved, buffer);
		if (!saved)
			return (free(buffer), NULL);
		if (bytes_read == 0 && *saved == '\0')
			return (free(buffer), free (saved), NULL);
		if (ft_strchr(saved, '\n'))
			break ;
	}
	return (free(buffer), saved);
}

char	*split_line(char *saved)
{
	char	*nextline;
	int		i;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	nextline = malloc((i + 1) * sizeof(char));
	if (!nextline)
		return (free(saved), NULL);
	nextline[i--] = '\0';
	while (i >= 0)
	{
		nextline[i] = saved[i];
		i--;
	}
	return (nextline);
}

char	*get_leftover(char *saved)
{
	char	*leftover;
	int		i;
	int		break_i;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	break_i = i;
	leftover = malloc((ft_strlen(saved + i) + 1) * sizeof(char));
	if (!leftover)
		return (free(saved), NULL);
	i = 0;
	while (saved[break_i])
		leftover[i++] = saved[break_i++];
	leftover[i] = '\0';
	return (free(saved), leftover);
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;
	char		*nextline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(saved), saved = NULL, NULL);
	if (!saved)
	{
		saved = malloc(1 * sizeof(char));
		if (!saved)
			return (NULL);
		saved[0] = '\0';
	}
	saved = read_until_break(saved, fd);
	if (!saved)
		return (NULL);
	nextline = split_line(saved);
	if (!nextline)
		return (saved = NULL, NULL);
	saved = get_leftover(saved);
	if (!saved)
		return (free(nextline), free(saved), NULL);
	return (nextline);
}
