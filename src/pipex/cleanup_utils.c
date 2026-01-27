/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:55:03 by hkonstan          #+#    #+#             */
/*   Updated: 2026/01/27 21:11:33 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/// @brief Closes both ends of a pipe file descriptor pair.
/// @details Convenience function that closes the read end and write end
///          of the given pipe. Used after finishing a pipe stage or when
///          cleaning up resources.
/// @param pipefd Array containing the pipe’s read and write file descriptors.
void	close_pipefd(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

/// @brief Handles execve() failures in a child process.
/// @details Prints an appropriate error message based on errno, frees all
///          program resources, and exits the child with the correct status:
///          127 for command not found, 126 for permission errors, and 1 for
///          all other failures. Uses perror() for system-derived messages.
/// @param data Program state containing command and environment info.
/// @param i Index of the command that failed to execute.
void	child_exec_error(t_data *data, int i)
{
	char	*cmd;

	cmd = data->cmds[i][0];
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

/// @brief Frees a NULL-terminated array of directory path strings.
/// @details Iterates through the array, freeing each path string and then
///          the array itself. Safely handles NULL input.
/// @param paths NULL-terminated array of path strings to free.
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

/// @brief Frees a NULL-terminated array of argv-style command arrays.
/// @details Frees each command’s argument list and then the command array
///          itself. Safely handles NULL input. The cmds pointer itself is
///          also freed at the end.
/// @param cmds Address of the NULL-terminated command array to free.
static void	free_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	if (!cmds)
		return ;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i++]);
	}
	free(cmds);
	cmds = NULL;
}

/// @brief Frees all dynamically allocated fields in the program state.
/// @details Releases memory allocated for commands, PATH directories,
///          child PID storage, and finally the t_data structure itself.
///          Safe to call multiple times or with NULL.
/// @param data Pointer to the program’s main state structure.
void	free_datas(t_data *data)
{
	if (data)
	{
		if (data->cmds)
			free_cmds(data->cmds);
		if (data->paths)
			free_paths(data->paths);
		if (data->pids)
			free(data->pids);
		free(data);
	}
}
