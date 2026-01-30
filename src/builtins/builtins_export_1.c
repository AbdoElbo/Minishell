# include "builtins.h"

static int	is_export_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_' ))
	{
		printf("export: `%s': not a valid identifier\n", str);
		return (0);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			printf("export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	update_node(t_envp *temp, char *str_iden, char *str_value, int has_value)
{
	temp->exported = 1;
	if (has_value)
	{
		if (temp->has_value)
			free(temp->value);
		temp->value = str_value;
		temp->has_value = 1;
	}
	else
		free(str_value);
	free(str_iden);
}

static t_envp	*create_node(t_envp **env, char *str_iden, char *str_value, int has_value)
{
	t_envp	*temp;

	temp = malloc(sizeof(t_envp));
	if (!temp)
		return (free(str_iden), free(str_value), NULL);
	temp->identifier = str_iden;
	temp->value = str_value;
	temp->has_value = has_value;
	temp->exported = 1;
	temp->next = *env;
	*env = temp;
	return (temp);
}

static int	export_each_var(t_envp **env, char *str)
{
	t_envp	*temp;
	char	*str_iden;
	char	*str_value;
	int		has_value;

	if (!is_export_valid_identifier(str))
		return (EXIT_FAILURE);
	if (!get_identifier_and_value(str, &str_iden, &str_value, &has_value))
		return (free(str_iden), free(str_value), EXIT_FAILURE);
	temp = find_env(*env, str_iden);
	if (temp)
		update_node(temp, str_iden, str_value, has_value);
	else
	{
		temp = create_node(env, str_iden, str_value, has_value);
		if (!temp)
			return (EXIT_FAILURE); // i free str_iden and str_value inside the create_node if something goes wrong
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(t_envp **env, int argc, char **argv)
{
	int	i;
	int	state;

	i = 1;
	state = EXIT_SUCCESS;
	if (argc == 1)
	{
		if (!print_export_format(*env))
			return (EXIT_FAILURE);
	}
	while (i < argc)
	{
		if (export_each_var(env, argv[i]) == EXIT_FAILURE)
			state = EXIT_FAILURE;
		i++;
	}
	return (state);
}
