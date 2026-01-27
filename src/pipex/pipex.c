/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:45:04 by hariskon          #+#    #+#             */
/*   Updated: 2026/01/27 21:08:25 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>
#include <stdio.h>

/// @brief Opens a file in input, output, or append mode.
/// @details For IN, opens the file read-only. For OUT, creates/truncates
///          the file for writing. For APPEND, creates and appends to the
///          file. On failure, prints an error using perror().
/// @param filename Path of the file to open.
/// @param in_out File mode selector (IN, OUT, or APPEND).
/// @return The file descriptor on success, or -1 on failure.
// static int	file_open(char *filename, enum e_in_out in_out)
// {
// 	int	fd;

// 	fd = -1;
// 	if (in_out == IN)
// 		fd = open(filename, O_RDONLY);
// 	else if (in_out == OUT)
// 		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else if (in_out == APPEND)
// 		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		perror(filename);
// 		fd = open("/dev/null", O_RDONLY);
// 		if (fd == -1)
// 			return (perror("Failed to open /dev/null"), -1);
// 	}
// 	return (fd);
// }

/// @brief Executes a single pipeline command in a child process.
/// @details Redirects input_fd to STDIN and the pipe write end to STDOUT,
///          closes unused file descriptors, and then calls execve() with
///          the selected command. On execve() failure, delegates to
///          child_exec_error().
/// @param data Pointer to the main program state.
/// @param i Index of the command to execute.
static void	child_proccess(t_data *data, int i)
{
	if (data->input_fd == -1)
		(close_pipefd(data->pipefd), free_datas(data), _exit(EXIT_FAILURE));
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
		(perror("Dup2 for STDIN failed"), _exit(EXIT_FAILURE));
	close(data->input_fd);
	if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
		(perror("Dup2 for STDOUT failed"), _exit(EXIT_FAILURE));
	close(data->pipefd[1]);
	close(data->pipefd[0]);
	execve(data->cmds[i][0], data->cmds[i], data->envp);
	child_exec_error(data, i);
}

/// @brief Executes all pipeline stages except the final command.
/// @details For each intermediate command, creates a pipe, forks a child,
///          runs the command in the child, and in the parent updates the
///          input_fd to the read end of the pipe while closing unused FDs.
/// @param data Pointer to the main program state.
/// @return 1 on success, or 0 if pipe or fork fails.
static int	execute_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i <= (data->cmds_count - 1))
	{
		if (i != data->cmds_count)
			if (pipe(data->pipefd) < 0)
				return (close(data->input_fd), perror("Pipe Failed"), 0);
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			return (perror("Fork failed"), 0);
		else if (data->pids[i] == 0)
			child_proccess(data, i);
		else
		{
			if (data->input_fd != -1)
				close(data->input_fd);
			close(data->pipefd[1]);
			data->input_fd = data->pipefd[0];
		}
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

/// @brief Entry point for the bonus pipex with here_doc support.
/// @details Initializes the program state, handles either here_doc input or
///          a regular infile, executes all pipeline commands, waits for all
///          children to finish, and frees resources before exiting.
/// @param argc Argument count from main().
/// @param argv Argument vector (supports both here_doc and normal mode).
/// @param envp Environment variables passed to the program.
/// @return The exit code of the last command in the pipeline, or 1 on setup
///         failure.
int	pipex(t_total_info *total)
{
	t_data	*data;

	if (!handle_heredocs(total->cmds))
		return (0);
	return (1);
	// else
		// data->input_fd = file_open(argv[1], IN);
	// if (data->input_fd == -1)
	// 	return (free_data(data), 1);
	if (!execute_loop(data))
		return (pid_wait_and_free(data));
	// if (!execute_last(data))
	// 	return (pid_wait_and_free(data));
	return (pid_wait_and_free(data));
}
