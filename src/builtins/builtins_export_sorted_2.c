/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_sorted_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:40:40 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:40:43 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_envp	*create_node_sorted(char *iden, char *value, int has_value,
	int exported)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->exported = exported;
	new_node->has_value = has_value;
	new_node->string = NULL;
	new_node->next = NULL;
	new_node->value = NULL;
	if (has_value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node), NULL);
	}
	new_node->identifier = ft_strdup(iden);
	if (!new_node->identifier)
		return (free (new_node->value), free(new_node), NULL);
	return (new_node);
}

int	create_sorted_env(t_envp **sorted, t_envp *env)
{
	t_envp	*new;

	while (env)
	{
		new = create_node_sorted(env->identifier, env->value,
				env->has_value, env->exported);
		if (!new)
			return (free_sorted_copy(*sorted), 0);
		env_addback(sorted, new);
		env = env->next;
	}
	sort_list(sorted);
	return (1);
}

void	free_sorted_copy(t_envp *sorted)
{
	t_envp	*temp;

	temp = sorted;
	while (sorted)
	{
		temp = sorted->next;
		if (sorted->identifier)
			free(sorted->identifier);
		if (sorted->value)
			free(sorted->value);
		free(sorted);
		sorted = temp;
	}
}

int	print_export_format(t_envp *env)
{
	t_envp	*s;
	t_envp	*head;

	s = NULL;
	if (!env)
		return (EXIT_FAILURE);
	if (!create_sorted_env(&s, env))
		return (EXIT_FAILURE);
	head = s;
	while (s)
	{
		if (s->exported)
		{
			if (!s->has_value)
				printf("declare -x %s\n", s->identifier);
			else
				printf("declare -x %s=\"%s\"\n", s->identifier, s->value);
		}
		s = s->next;
	}
	free_sorted_copy(head);
	return (EXIT_SUCCESS);
}
