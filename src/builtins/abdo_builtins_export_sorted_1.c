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

t_env	*create_node(char *iden, char *value, int has_value, int exported)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
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
