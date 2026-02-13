
#include "builtins.h"

t_envp	*create_node_sorted(char *iden, char *value, int has_value, int exported)
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
	t_envp *new;

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
	t_envp	*sorted;
	t_envp	*sorted_head;

	sorted = NULL;
	if (!env)
		return (EXIT_FAILURE);
	if (!create_sorted_env(&sorted, env))
		return (EXIT_FAILURE);
	sorted_head = sorted;
	while (sorted)
	{
		if (sorted->exported)
		{
			if (!sorted->has_value)
				printf("declare -x %s\n", sorted->identifier);
			else
				printf("declare -x %s=\"%s\"\n", sorted->identifier, sorted->value);
		}
		sorted = sorted->next;
	}
	free_sorted_copy(sorted_head);
	return (EXIT_SUCCESS);
}
