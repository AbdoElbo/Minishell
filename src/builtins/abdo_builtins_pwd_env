#include "abdo.h"

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
		if (env->exported && env->has_value)
			printf("%s=%s\n", env->identifier, env->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

