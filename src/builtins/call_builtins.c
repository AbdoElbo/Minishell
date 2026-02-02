
#include "builtins.h"

int	is_builtin(t_data *data)
{
	if (ft_strncmp(data->cmds->argv[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "unset", 5) == 0)
		return (1);
	return (0);
}

int	call_builtins(t_data *data)
{
	int	status;

	status = 0;
	write(2, "THIS IS A BUILTINNNNN\n", 22);
	if (ft_strncmp(data->cmds->argv[0], "cd", 2) == 0)
		status = builtin_cd(&data->envp_list, data->cmds->argc, data->cmds->argv);
	else if (ft_strncmp(data->cmds->argv[0], "echo", 4) == 0)
		status = builtin_echo(data->cmds->argv);
	// else if (ft_strncmp(data->cmds->argv[0], "exit", 4) == 0)
	// 	status = builtin_exit(); // later
	else if (ft_strncmp(data->cmds->argv[0], "export", 6) == 0)
		status = builtin_export(&data->envp_list, data->cmds->argc, data->cmds->argv);
	else if (ft_strncmp(data->cmds->argv[0], "pwd", 3) == 0)
		status = builtin_pwd();
	else if (ft_strncmp(data->cmds->argv[0], "env", 3) == 0)
		status = builtin_env(&data->envp_list);
	else if (ft_strncmp(data->cmds->argv[0], "unset", 5) == 0)
		status = builtin_unset(&data->envp_list, data->cmds->argc, data->cmds->argv);
	return (status);
}
