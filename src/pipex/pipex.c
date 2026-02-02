/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:45:04 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/02 21:58:32 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>
#include <stdio.h>
#include "../include/builtins.h"

//I NEED TO FIX THE ISSUE OF NOT EXITING WHEN THE FILE DOESNT EXIST.
static int	file_open(char *filename, enum e_in_out in_out)
{
	int	fd;

	fd = -1;
	if (in_out == IN)
		fd = open(filename, O_RDONLY);
	else if (in_out == OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (in_out == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	// if (fd == -1)
	// {
	// 	perror(filename);
	// 	fd = open("/dev/null", O_RDONLY);
	// 	if (fd == -1)
	// 		return (perror("Failed to open /dev/null"), -1);
	// }
	return (fd);
}

static void	handle_redirections(t_data *data)//Needs to be smaller!!!
{
	t_redir	*temp;
	int		input;
	int		output;

	input = data->input_fd;
	output = data->output_fd;
	temp = data->cmds->redir;
	while (temp)
	{
		if (temp->type == REDIR_APPEND)
		{
			if (data->output_fd != 1)
				close(data->output_fd);
			temp->fd = file_open(temp->file, APPEND);
			if (temp->fd == -1)
				(perror(temp->file), _exit(EXIT_FAILURE));
			data->output_fd = temp->fd;
		}
		else if (temp->type == REDIR_OUT)
		{
			if (data->output_fd != 1)
				close(data->output_fd);
			temp->fd = file_open(temp->file, OUT);
			if (temp->fd == -1)
				(perror(temp->file), _exit(EXIT_FAILURE));
			data->output_fd = temp->fd;
		}
		else if (temp->type == REDIR_IN)
		{
			if (data->input_fd != 0)
				close(data->input_fd);
			temp->fd = file_open(temp->file, IN);
			if (temp->fd == -1)
				(perror(temp->file), _exit(EXIT_FAILURE));
			data->input_fd = temp->fd;
		}
		else if (temp->type == REDIR_HEREDOC)
		{
			if (data->input_fd != 0)
				close(data->input_fd);
			data->input_fd = temp->fd;
		}
		temp = temp->next;
	}
	if (input != data->input_fd)
	{
		if (dup2(data->input_fd, STDIN_FILENO) == -1)
			(perror("Dup2 for STDIN failed"), _exit(EXIT_FAILURE));
		close(data->input_fd);
	}
	if (output != data->output_fd)
	{
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
			(perror("Dup2 for STDOUT failed"), _exit(EXIT_FAILURE));
		close(data->output_fd);
	}
}

static void	handle_parent(t_data *data)
{
	if (data->input_fd != 0)
		close(data->input_fd);
	if (data->cmds->next)
	{
		close(data->pipefd[1]);
		data->input_fd = data->pipefd[0];
	}
}

static void	child_proccess(t_data *data)
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
		_exit(call_builtins(data));
	else
	{
		path_check_one(data->cmds->argv, data->paths);
		execve(data->cmds->argv[0], data->cmds->argv, data->envp);
		child_exec_error(data);
	}
}

static int	execute_loop(t_data *data) //need to make it 25 lines
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
			child_proccess(data);
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

	if (!handle_heredocs(total->cmds))
		return (1);
	data = setup_datas(total);
	if (!data)
		return (1);
	if (is_builtin(data) && ft_cmds_size(total->cmds) == 1)
	{
		exit = call_builtins(data);
		return (free_datas(data), 1);
	}
	else
	{
		if (!execute_loop(data))
			return (pid_wait_and_free(data));
		return (pid_wait_and_free(data));
	}
}
