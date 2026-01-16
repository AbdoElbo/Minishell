# include "abdo.h"

int	is_export_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_' ))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static t_env	*find_env(t_env *env, char *identifier)
{
	int	len;

	len = ft_strlen(identifier);
	while (env)
	{
		if (ft_strncmp(env->identifier, identifier, len) == 0
			&& env->identifier[len] == '\0')
			return (env);
		env = env->next;
	}
	return (NULL);
}

static int	export_each_var(t_env **env, char *str)
{
	t_env	*temp;
	char	*str_iden;
	char	*str_value;
	int		has_value;

	if (!is_export_valid_identifier(str))
	{
		printf("export: `%s': not a valid identifier\n", str);
		return (EXIT_FAILURE);
	}
	if (!get_identifier_and_value(str, &str_iden, &str_value, &has_value))
		return (free(str_iden), free(str_value), EXIT_FAILURE);
	temp = find_env(*env, str_iden);
	if (temp)
	{
		if (temp->has_value)
		{
			free(temp->value);
			temp->value = str_value;
			temp->has_value = 1;
		}
		else
			free(temp->value);
	}
	else
	{
		temp = malloc(sizeof(t_env));
		if (!temp)
			return (free(str_iden), free(str_value), EXIT_FAILURE);
		temp->identifier = str_iden;
		temp->value = str_value;
		temp->has_value = has_value;
		temp->next = *env;
		*env = temp;
	}
	return (EXIT_SUCCESS);
}


int	builtin_export(t_env **env, int argc, char **argv)
{
	int	i;
	int	state;

	i = 1;
	state = EXIT_SUCCESS;
	if (argc == 1)
		//printf the whole env with the export format
	while (i < argc)
	{
		if (export_each_var(env, argv[i]) == EXIT_FAILURE)
			state = EXIT_FAILURE;
		i++;
	}
	return (state);
}


// int	builtin_echo(char *env, int argc, char **argv)
// {
// 	int	i;
// 	int	new_line;

// 	i = 1;
// 	new_line = newline_option(argv) // returns
// 	while (i < argc)
// 	{
// 		printf("%s", argv[i]);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }



// int		builtin_exit(char *env)
// {

// }


//bca
//abc
// acb
// bac
//
