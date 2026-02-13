/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:45:04 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/13 16:12:49 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>
#include <stdio.h>
#include "../include/builtins.h"

static void	handle_parent(t_data *data)
{
	t_redir	*temp;

	temp = data->cmds->redir;
	while (temp)
	{
		if (temp->type == REDIR_HEREDOC && temp->fd > 2)
			close(temp->fd);
		temp = temp->next;
	}
	if (data->input_fd != 0)
		close(data->input_fd);
	if (data->cmds->next)
	{
		close(data->pipefd[1]);
		data->input_fd = data->pipefd[0];
	}
}

static void	child_proccess(t_data *data, t_total_info *total)
{
	if (data->input_fd != 0)
	{
		if (dup2(data->input_fd, STDIN_FILENO) == -1)
			(perror("Dup2 for STDIN failed"), _exit(EXIT_FAILURE));
		close(data->input_fd);
	}
	if (data->cmds->next)
	{
		if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
			(perror("Dup2 for STDOUT failed"), _exit(EXIT_FAILURE));
		close(data->pipefd[1]);
	}
	handle_redirections(data);
	if (data->cmds->next)
		close(data->pipefd[0]);
	if (is_builtin(data))
		_exit(call_builtins(data, total));
	else if (data->cmds->argv[0])
	{
		path_check_one(data->cmds->argv, data->paths);
		execve(data->cmds->argv[0], data->cmds->argv, data->envp_arr);
		child_exec_error(data);
	}
	_exit(EXIT_SUCCESS);
}

static int	execute_loop(t_data *data, t_total_info *total)
{
	int		i;

	i = 0;
	while (data->cmds)
	{
		if (data->cmds->next)
			if (pipe(data->pipefd) < 0)
				return (close(data->input_fd), perror("Pipe Failed"), 0);
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			return (perror("Fork failed"), 0);
		else if (data->pids[i] == 0)
			child_proccess(data, total);
		else
			handle_parent(data);
		data->cmds = data->cmds->next;
		i++;
	}
	return (1);
}

static int	handle_heredocs(t_cmds *cmds)
{
	t_redir	*temp;

	while (cmds)
	{
		temp = cmds->redir;
		while (temp)
		{
			if (temp->type == REDIR_HEREDOC && !read_heredoc(temp))
				return (0);
			temp = temp->next;
		}
		cmds = cmds->next;
	}
	return (1);
}

int	pipex(t_total_info *total)
{
	t_data	*data;
	int		exit;

	data = setup_datas(total);
	if (!data || !handle_heredocs(total->cmds))
		return (1);
	if (ft_cmds_size(total->cmds) == 1)
	{
		if (is_builtin(data) || !total->cmds->argv[0])
		{
			exit = handle_redir_parent(data);
			if (exit)
				return (restore_parent_stdio(total), free_datas(data), exit);
		}
		if (is_builtin(data))
		{
			exit = call_builtins(data, total);
			restore_parent_stdio(total);
			return (free_datas(data), exit);
		}
		if (!total->cmds->argv[0])
			return (free_datas(data), exit);
	}
	return (execute_loop(data, total), pid_wait_and_free(data));
}
