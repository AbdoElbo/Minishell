#include "abdo.h"

int	is_valid_identifier(char *str)
{
	int i;
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

static void	delete_node(t_env **env, t_env *prev, t_env *curr)
{
	if (!env || !curr)
		return;
	if (prev)
		prev->next = curr->next;
	else
		*env = curr->next;
	free(curr->string);
	free(curr);
}

int	builtin_unset(t_env **env, char *str)
{
	t_env *prev;
	t_env *curr;
	int len;

	if (!env || !*env || !str)
		return (EXIT_SUCCESS);
	if (!is_valid_identifier(str))
	{
		printf("unset: `%s': not a valid identifier\n", str);
		return (EXIT_FAILURE);
	}
	curr = *env;
	prev = NULL;
	len = ft_strlen(str);
	while (curr)
	{
		if (ft_strncmp(str, curr->string, len) == 0 && curr->string[len] == '=')
			return (delete_node(env, prev, curr), EXIT_SUCCESS);
		prev = curr;
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

int	builtin_pwd(void)
{
	char	*working_dir;

	working_dir = getcwd(NULL, 0);
	if (!working_dir)
		return (EXIT_FAILURE);
	printf("%s\n", working_dir);
	free(working_dir);
	return (EXIT_SUCCESS);
}

int	builtin_env(t_env *env)
{
	if (!env)
		return (EXIT_SUCCESS); // apparently, bash retuns 0 (SUCCESS) even if env is empty
	while (env)
	{
		if (env->string)
			printf("%s\n", env->string);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
