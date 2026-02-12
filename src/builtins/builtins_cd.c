#include "builtins.h"

static int	change_old_path(t_envp **env, char *current_pwd)
{
	t_envp	*temp;

	if (!*env)
		return (EXIT_FAILURE);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp("OLDPWD=", temp->string, 7) == 0)
		{
			free(temp->string);
			temp->string = ft_strjoin("OLDPWD=", current_pwd);
			if (!temp->string)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

static int	update_new_path(t_envp **env)
{
	t_envp	*temp;
	char	*new_path;

	if (!*env)
		return (EXIT_FAILURE);
	temp = *env;
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (EXIT_FAILURE);
	while (temp)
	{
		if (ft_strncmp("PWD=", temp->string, 4) == 0)
		{
			free(temp->string);
			temp->string = ft_strjoin("PWD=", new_path);
			if (!temp->string)
				return (free(new_path), EXIT_FAILURE);
			free(new_path);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (free(new_path), EXIT_FAILURE);
}

static int	rollback_env(t_envp **env, char **old, char **pwd)
{
	t_envp	*temp;

	if (!*env)
		return (free(*old), free(*pwd), EXIT_FAILURE);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp("OLDPWD=", temp->string, 7) == 0)
		{
			free(temp->string);
			temp->string = ft_strdup(*old);
			if (!temp->string)
				return (free(*old), free(*pwd), EXIT_FAILURE);
		}
		else if (ft_strncmp("PWD=", temp->string, 4) == 0)
		{
			free(temp->string);
			temp->string = ft_strdup(*pwd);
			if (!temp->string)
				return (free(*old), free(*pwd), EXIT_FAILURE);
		}
		temp = temp->next;
	}
	return (free(*old), free(*pwd), EXIT_SUCCESS);
}

static char	*get_cd_target(int argc, char **argv)
{
	char	*str;

	if (argc > 2)
		return (write(2, "too many arguments\n", 19), NULL);
	if (argc == 1)
	{
		str = getenv("HOME");
		if (!str)
			return (write(2, "cd: HOME not set\n", 18), NULL);
		return (str);
	}
	return (argv[1]);
}

int	builtin_cd(t_envp **env, int argc, char **argv)
{
	char	*copy_old;
	char	*copy_pwd;
	char	*str;

	str = get_cd_target(argc, argv);
	if (!str || !*env)
		return (EXIT_FAILURE);
	copy_old = get_envp_value(*env, "OLDPWD=");
	if (!copy_old)
		return (EXIT_FAILURE);
	copy_pwd = get_envp_value(*env, "PWD=");
	if (!copy_pwd)
		return (free(copy_old), EXIT_FAILURE);
	if (change_old_path(env, copy_pwd) == EXIT_FAILURE)
		return (rollback_env(env, &copy_old, &copy_pwd), EXIT_FAILURE);
	if (chdir(str) != 0)
	{
		write(2, "cd: ", 4);
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 28);
		return (rollback_env(env, &copy_old, &copy_pwd), EXIT_FAILURE);
	}
	if (update_new_path(env) == EXIT_FAILURE)
		return (rollback_env(env, &copy_old, &copy_pwd), EXIT_FAILURE);
	return (free(copy_old), free(copy_pwd), EXIT_SUCCESS);
}
