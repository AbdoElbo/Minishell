/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:15:15 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:15:17 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
