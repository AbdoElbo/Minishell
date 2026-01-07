# include "abdo.h"

int		builtin_cd(t_env **env)
{
	if (!*env)
		return (0);
	while (env)
	{
		if ()
	}
}

int		builtin_pwd(t_env **env)
{
	t_env	*tmp;

	if (!*env)
		return (0);
	tmp = *env;
	while (tmp)
	{
		if (tmp->string[0] == "P" && tmp->string[1] == "W"
			&& tmp->string[2] == "D")
		{
			printf("%s\n", tmp->string);
			retunr (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		builtin_env(t_env **env)
{
	t_env	*tmp;

	if (!*env)
		return (0);
	tmp = *env;
	while (tmp)
	{
		printf("%s\n", tmp->string);
		tmp = tmp->next;
	}
	return (1);
}

int		builtin_unset(t_env **env)
{

}



