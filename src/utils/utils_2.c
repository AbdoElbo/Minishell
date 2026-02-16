/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:15:40 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/16 16:54:47 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_arg(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	total_len;
	size_t	i;

	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) +2;
	new_string = malloc(total_len);
	if (new_string == NULL)
		return (NULL);
	if (s1)
		while (*s1)
			new_string[i++] = *s1++;
	if (i != 0)
		new_string[i++] = ' ';
	if (s2)
		while (*s2)
			new_string[i++] = *s2++;
	new_string[i] = '\0';
	return (new_string);
}

t_envp	*new_envp_node(char *str)
{
	t_envp	*new_envp;

	new_envp = ft_calloc(1, sizeof(t_envp));
	if (!new_envp)
		return (write(2, "Memaloc 2 fail new_envp", 23), NULL);
	new_envp->string = ft_strdup(str);
	if (!new_envp->string)
		return (write(2, "Memaloc 2 fail new_envp", 23), free(new_envp), NULL);
	new_envp->next = NULL;
	return (new_envp);
}

static int	update_env(t_envp **env)
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
			return (free(identifier), free(value), 0);
		temp->identifier = identifier;
		temp->value = value;
		temp->has_value = has_value;
		temp->exported = 1;
		temp = temp->next;
	}
	return (1);
}

int	treat_empty_envp(t_total_info *total)
{
	char	*path;
	char	*temp;
	t_envp	*new_envp;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (0);
	path = ft_strjoin("PWD=", temp);
	if (!path)
		return (free(temp), 0);
	free(temp);
	new_envp = new_envp_node(path);
	if (!new_envp)
		return (ft_t_envp_clear(&new_envp), 0);
	ft_t_envp_addback(&total->our_envp, new_envp);
	if (!update_env(&total->our_envp))
		return (ft_t_envp_clear(&new_envp), 0);
	return (1);
}

int	copy_envp(t_total_info *total, char **envp)
{
	int		i;
	t_envp	*new_envp;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		new_envp = new_envp_node(envp[i]);
		if (!new_envp)
			return (ft_t_envp_clear(&new_envp), 0);
		ft_t_envp_addback(&total->our_envp, new_envp);
		i++;
	}
	if (!update_env(&total->our_envp))
		return (ft_t_envp_clear(&new_envp), 0);
	return (1);
}
