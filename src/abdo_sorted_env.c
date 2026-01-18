#include "abdo.h"

void	free_sorted_copy(t_env *sorted)
{
	t_env	*temp;

	temp = sorted;
	while (sorted)
	{
		temp = sorted->next;
		free(sorted->identifier);
		free(sorted->value);
		free(sorted);
		sorted = temp;
	} 
}

int	create_sorted_env(t_env *env)
{
	t_env *temp;
	t_env *new;

	if (!env)
		return (0);
	new = NULL;
	temp = env;
	while (temp)
	{
		env_addback(&new, temp);
		temp = temp->next;
	}
	return (1);
}

// static int	print_export_format(t_env *env)
// {
// 	t_env	*sorted;

// 	sorted = NULL;
// 	if (!env)
// 		return (EXIT_FAILURE);
// 	sorted = create_sorted_env(env);
// 	if (!sorted)
// 		return (EXIT_FAILURE);
// 	while (sorted)
// 	{
// 		if (sorted->exported)
// 		{
// 			if (!sorted->has_value)
// 				printf("declare -x %s\n", sorted->identifier);
// 			else
// 				printf("declare -x %s=\"%s\"\n", sorted->identifier, sorted->value);
// 		}
// 		sorted = sorted->next;
// 	}
// 	free_sorted_copy(sorted);
// 	return (EXIT_SUCCESS);
// }