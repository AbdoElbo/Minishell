#include "builtins.h"

void	env_addback(t_envp **env, t_envp *new)
{
	t_envp	*temp;

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

t_envp	*env_last(t_envp *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	swap_nodes(t_envp **sorted, t_envp **prev, t_envp **curr, int *swap)
{
	t_envp	*temp;

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

void	sort_list(t_envp **sorted)
{
	t_envp	*curr;
	t_envp	*prev;
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
