/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:40:59 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:41:04 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "pipex.h"

int	is_builtin(t_data *data)
{
	if (!data->cmds->argv[0])
		return (0);
	if (ft_strncmp(data->cmds->argv[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(data->cmds->argv[0], "unset", 6) == 0)
		return (1);
	return (0);
}

int	call_builtins(t_data *data, t_total_info *total)
{
	int		status;
	t_cmds	*cmds;

	status = 0;
	cmds = data->cmds;
	if (ft_strncmp(cmds->argv[0], "cd", 3) == 0)
		status = builtin_cd(&total->our_envp, cmds->argc, cmds->argv);
	else if (ft_strncmp(cmds->argv[0], "echo", 5) == 0)
		status = builtin_echo(cmds->argv);
	else if (ft_strncmp(cmds->argv[0], "exit", 5) == 0)
		status = builtin_exit(cmds->argc, cmds->argv, total);
	else if (ft_strncmp(cmds->argv[0], "export", 7) == 0)
		status = builtin_export(&total->our_envp, cmds->argc, cmds->argv);
	else if (ft_strncmp(cmds->argv[0], "pwd", 4) == 0)
		status = builtin_pwd();
	else if (ft_strncmp(cmds->argv[0], "env", 4) == 0)
		status = builtin_env(cmds->argc, cmds->argv, &total->our_envp);
	else if (ft_strncmp(cmds->argv[0], "unset", 6) == 0)
		status = builtin_unset(&total->our_envp, cmds->argc, cmds->argv);
	free_arr(data->envp_arr);
	data->envp_arr = change_to_arr(total->our_envp);
	if (!data->envp_arr)
		return (write(2, "Alloc failed - call_builtins\n", 29), free(total), 1);
	return (status);
}
