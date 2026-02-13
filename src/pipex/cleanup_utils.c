/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:55:03 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/13 16:13:10 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/builtins.h"

int	file_open(char *filename, enum e_in_out in_out)
{
	int	fd;

	fd = -1;
	if (in_out == IN)
		fd = open(filename, O_RDONLY);
	else if (in_out == OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (in_out == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

void	close_pipefd(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	child_exec_error(t_data *data)
{
	char	*cmd;

	cmd = data->cmds->argv[0];
	if (errno == ENOENT)
	{
		write(2, "command not found: ", 19);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		free_datas(data);
		_exit(127);
	}
	if (errno == EACCES)
	{
		write(2, "permission denied: ", 19);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		free_datas(data);
		_exit(126);
	}
	perror(cmd);
	free_datas(data);
	_exit(1);
}

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	paths = NULL;
}

void	free_datas(t_data *data)
{
	if (data)
	{
		if (data->paths)
			free_paths(data->paths);
		if (data->pids)
			free(data->pids);
		if (data->envp_arr)
			free_arr(data->envp_arr);
		free(data);
	}
}
