# include "builtins.h"

char	*get_envp_value(t_envp *env, char *str)
{
	char	*new_str;
	int		len;

	if (!env)
		return (NULL);
	len = ft_strlen(str);
	while (env)
	{
		if (ft_strncmp(str, env->string, len) == 0)
		{
			new_str = ft_strdup(env->string);
			if (!new_str)
				return (NULL);
			return (new_str);
		}
		env = env->next;
	}
	return (NULL);
}

static int	change_old_path(t_envp **env, char *current_pwd)
{
	t_envp	*temp;

	if (!*env)
		return (EXIT_FAILURE);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp("OLDPWD=", temp->string, 7) == 0) // ft_strncmp return 0 if there's no differnece between the two strings
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
		if (ft_strncmp("PWD=", temp->string, 4) == 0) // ftstrncmp retunr 0 if there's no differnece between the two strings
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

int	builtin_cd(t_envp **env, char *new_path)
{
	char	*copy_old;
	char	*copy_pwd;

	if (!*env)
		return (EXIT_FAILURE);
	if (!new_path)
		new_path = getenv("HOME");
	if (!new_path)
		return (printf("cd: HOME not set\n"), EXIT_FAILURE);
	copy_old = get_envp_value(*env, "OLDPWD=");
	if (!copy_old)
		return (EXIT_FAILURE);
	copy_pwd = get_envp_value(*env, "PWD=");
	if (!copy_pwd)
		return (free(copy_old), EXIT_FAILURE);
	if (change_old_path(env, copy_pwd) == EXIT_FAILURE)
		return (rollback_env(env, &copy_old, &copy_pwd), EXIT_FAILURE);
	if (chdir(new_path) != 0)
	{
		printf("cd: %s: No such file or directory\n", new_path);
		return (rollback_env(env, &copy_old, &copy_pwd), EXIT_FAILURE);
	}
	if (update_new_path(env) == EXIT_FAILURE)
		return (rollback_env(env, &copy_old, &copy_pwd), EXIT_FAILURE);
	return (free(copy_old), free(copy_pwd), EXIT_SUCCESS);
}

