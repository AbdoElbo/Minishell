
#include "builtins.h"

int	create_sorted_env(t_env **sorted, t_env *env)
{
	t_env *new;

	while (env)
	{
		new = create_node(env->identifier, env->value,
			env->has_value, env->exported);
		if (!new)
			return (free_sorted_copy(*sorted), 0);
		env_addback(sorted, new);
		env = env->next;
	}
	sort_list(sorted);
	return (1);
}

void	free_sorted_copy(t_env *sorted)
{
	t_env	*temp;

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

int	print_export_format(t_env *env)
{
	t_env	*sorted;
	t_env	*sorted_head;

	sorted = NULL;
	if (!env)
		return (EXIT_FAILURE);
	if (!create_sorted_env(&sorted ,env))
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
