#include "builtins.h"

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

int	builtin_env(int argc, char **argv, t_envp **env)
{
	t_envp	*temp;

	(void)argv;
	if (!env)
		return (EXIT_SUCCESS);
	if (argc != 1)
		return (127); // talk to harris about this (i hardcoded this)
	temp = *env;
	while (temp)
	{
		if (temp->exported && temp->has_value)
			printf("%s=%s\n", temp->identifier, temp->value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
