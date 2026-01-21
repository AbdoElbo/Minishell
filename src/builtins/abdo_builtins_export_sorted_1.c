#include "abdo.h"

void	env_addback(t_env **env, t_env *new)
{
	t_env	*temp;

	if (env != NULL)
	{
		if (*env == NULL)
			*env = new;
		else
		{
			temp = env_last(*env);
			temp->next = new;
		}
	}
}

t_env	*env_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	swap_nodes(t_env **sorted, t_env **prev, t_env **curr, int *swap)
{
	t_env	*temp;

	if ((*prev))
		(*prev)->next = (*curr)->next;
	else
		*sorted = (*curr)->next;
	temp = (*curr)->next->next;
	(*curr)->next->next = (*curr);
	(*curr)->next = temp;
	if ((*prev))
		(*curr) = (*prev)->next;
	else
		(*curr) = *sorted;
	*swap = 1;
}

void	sort_list(t_env **sorted)
{
	t_env	*curr;
	t_env	*prev;
	int		swap;
	int		len;

	if (!*sorted || env_size(*sorted) == 1)
		return ;
	swap = 1;
	while (swap)
	{
		curr = *sorted;
		prev = NULL;
		swap = 0;
		while (curr && curr->next)
		{
			len = ft_strlen(curr->identifier) + 1;
			if (ft_strncmp(curr->identifier, curr->next->identifier, len) > 0)
				swap_nodes(sorted, &prev, &curr, &swap);
			else
			{
				prev = curr;
				curr = curr->next;
			}
		}
	}
}
