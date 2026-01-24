#include "builtins.h"

static int	is_unset_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	delete_node(t_envp **env, t_envp *prev, t_envp *curr)
{
	if (!env || !curr)
		return;
	if (prev)
		prev->next = curr->next;
	else
		*env = curr->next;
	free(curr->string);
	free(curr->identifier);
	free(curr->value);
	free(curr);
}

static int	unset_each_var(t_envp **env, char *str)
{
	int		len;
	t_envp	*prev;
	t_envp	*curr;

	if (!env || !*env || !str)
		return (EXIT_SUCCESS);
	if (!is_unset_valid_identifier(str))
	{
		printf("unset: `%s': not a valid identifier\n", str);
		return (EXIT_FAILURE);
	}
	len = ft_strlen(str);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->identifier, str, len) == 0
			&& curr->identifier[len] == '\0')
			return (delete_node(env, prev, curr), EXIT_SUCCESS);
		prev = curr;
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_envp **env, int argc, char **argv)
{
	int	i;
	int	state;

	i = 1;
	state = EXIT_SUCCESS;
	while (i < argc)
	{
		if (unset_each_var(env, argv[i]) == EXIT_FAILURE)
			state = EXIT_FAILURE;
		i++;
	}
	return (state);
}

