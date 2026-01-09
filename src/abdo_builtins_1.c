# include "abdo.h"

int	change_old_path(t_env **env)
{
	t_env	*temp;

	if (!*env)
		return (EXIT_FAILURE);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp("OLDPWD=", temp->string, 7) == 0) // ft_strncmp return 0 if there's no differnece between the two strings
		{

		}
		temp = temp->next;
	}
}

int	update_new_path(t_env **env)
{
	t_env	*temp;

	if (!*env)
		return (EXIT_FAILURE);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp("PWD=", temp->string, 4) == 0) // ftstrncmp retunr 0 if there's no differnece between the two strings
		{

		}
		temp = temp->next;
	}
}

int		builtin_cd(t_env **env, char *new_path)
{
	if (!*env)
		return (EXIT_FAILURE);
	if (!new_path)
	{
		new_path = getenv("HOME");
		if (!new_path)
			return (printf("cd: HOME not set\n"), EXIT_FAILURE);
	}
	change_old_path(env);
	if (chdir(new_path) != 0)
	{
		printf("cd: %s: No such file or directory\n", new_path);
		return (EXIT_FAILURE);
	}
	update_new_path(env);
	return (EXIT_SUCCESS);
}

int		builtin_pwd(void)
{
	char	*working_dir;

	working_dir = getcwd(NULL, 0);
	if (!working_dir)
		return (EXIT_FAILURE);
	printf("%s\n", working_dir);
	free(working_dir);
	return (EXIT_SUCCESS);
}

// int		builtin_env(t_env **env)
// {
// 	t_env	*tmp;

// 	if (!*env)
// 		return (0);
// 	tmp = *env;
// 	while (tmp)
// 	{
// 		printf("%s\n", tmp->string);
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }

// int		builtin_unset(t_env **env)
// {

// }



