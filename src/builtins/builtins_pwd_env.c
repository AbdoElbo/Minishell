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

int	builtin_env(t_envp **env)
{
	t_envp	*temp;

	if (!env)
		return (EXIT_SUCCESS);
	temp = *env;
	while (temp)
	{
		if (temp->exported && temp->has_value)
			printf("%s=%s\n", temp->identifier, temp->value);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
