#include "minishell.h"

static t_envp	*find_value(t_envp *env, char *identifier)
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
	return (write(2, "couldn't find the identifier\n", 29), NULL);
}

static int	treat_invalid_variable(t_total_info *total, t_expand *data)
{
	char	*exit_code;

	if (data->redir_file[data->i_redir + 1] == '?')
	{
		exit_code = ft_itoa(total->exit_code);
		if (!exit_code)
			return (write(2, "mem aloc fail in expand_var", 27), 0);
		if (ft_strlen(data->temp) + ft_strlen(exit_code) >= data->redir_size)
		{
			if (!increase_buffer(&data->temp, &data->redir_size, 0))
				return (free(exit_code), 0);
		}
		ft_memcpy(data->temp + ft_strlen(data->temp),
			exit_code, ft_strlen(exit_code));
		data->i_redir += 1;
		free(exit_code);
	}
	else if (data->redir_file[data->i_redir + 1]
		== '\0' || ft_isspace(data->redir_file[data->i_redir + 1]))
		ft_memcpy(data->temp + ft_strlen(data->temp), "$", 1);
	else
		data->i_redir += 1;
	return (1);
}

static char	*extract_variable(t_expand *data, int *var_len)
{
	int		i;
	char	*substring;

	*var_len = 0;
	i = data->i_redir;
	while (ft_isalnum(data->redir_file[i]) || data->redir_file[i] == '_')
	{
		i++;
		(*var_len)++;
		if ((ft_strlen(data->temp) + *var_len) > data->redir_size - 1
			&& !increase_buffer(&data->temp, &data->redir_size, *var_len))
			return (NULL);
	}
	substring = ft_substr(data->redir_file, data->i_redir, *var_len);
	if (!substring)
		return (write(2, "substr fail in extract_variable", 31), NULL);
	return (substring);
}

static int	treat_valid_variable(t_total_info *total, t_expand *data)
{
	t_envp	*temp;
	int		var_len;
	char	*variable;

	var_len = 0;
	data->i_redir++;
	variable = extract_variable(data, &var_len);
	if (!variable)
		return (0);
	data->i_redir += ft_strlen(variable) - 1;
	temp = find_value(total->our_envp, variable);
	if (!temp)
		return (free(variable), 0);
	var_len = ft_strlen(temp->value);
	if ((ft_strlen(data->temp) + var_len) > data->redir_size - 2
		&& (!increase_buffer(&data->temp, &data->redir_size, var_len)))
		return (free(variable), 0);
	ft_memcpy(data->temp + ft_strlen(data->temp),
		temp->value, ft_strlen(temp->value));
	return (free(variable), 1);
}

int	expand_var_redir(t_total_info *total, t_expand *data)
{
	char	*argv;
	int		i;

	argv = data->redir_file;
	i = data->i_redir;
	if (!(ft_isalpha(argv[i + 1]) || argv[i + 1] == '_' ))
	{
		if (!treat_invalid_variable(total, data))
			return (0);
	}
	else
	{
		if (!treat_valid_variable(total, data))
			return (0);
	}
	return (1);
}
