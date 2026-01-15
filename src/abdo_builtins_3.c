# include "abdo.h"

int	is_export_valid_identifier(char *str)
{
	int	i;
	int	counter;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_' ))
		return (0);
	i = 1;
	counter = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '='))
			return (0);
		if (str[i] == '=')
			break ;
		i++;
	}
	return (1);
}

static int	export_each_var(t_env **env, char *str)
{
	t_env *temp;
	int len;
	int updated;

	if (!env)
		return (EXIT_SUCCESS);
	if (!*env)
		return (add_node(env, temp, str), EXIT_SUCCESS);
	if (!str)
		//printf the whole env with the eport format
	if (!is_export_valid_identifier(str))
	{
		printf("export: `%s': not a valid identifier\n", str);
		return (EXIT_FAILURE);
	}
	len = ft_strlen(str);
	updated = 0;
	temp = *env;
	while (temp)
	{
		if (ft_strncmp(str, temp->string, len) == 0 && temp->string[len] == '=')
			return (updated = 1, update_node(env, temp, str), EXIT_SUCCESS);
		temp = temp->next;
	}
	if (!updated)
		add_node(env, temp, str);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_env **env, int argc, char **argv)
{
	int	i;
	int	state;

	i = 1;
	state = EXIT_SUCCESS;
	while (i < argc)
	{
		if (export_each_var(env, argv[i]) == EXIT_FAILURE)
			state = EXIT_FAILURE;
		i++;
	}
	return (state);
}


int	builtin_echo(char *env, int argc, char **argv)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	while (i < argc)
	{

		i++;
	}
	return (EXIT_SUCCESS);
}



// int		builtin_exit(char *env)
// {

// }

