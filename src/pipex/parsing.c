/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:12:04 by hariskon          #+#    #+#             */
/*   Updated: 2026/01/27 21:11:12 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/// @brief Parses and splits each command string into its argument list.
/// @details Allocates the cmds array and uses ft_split() to break each
///          command into tokens separated by spaces. If a command results
///          in no tokens (empty or whitespace-only), it is replaced with a
///          single empty string to allow consistent error handling later.
///          Any memory allocation failure stops the process prints the 
///			 corresponding error and returns 0.
/// @param data Pointer to the main program state.
/// @return 1 on success, or 0 if any allocation fails.
static int	parse_argv(t_data *data)
{
	int		i;

	i = 0;
	data->cmds = ft_calloc((data->cmds_count + 1), sizeof(char **));
	if (data->cmds == NULL)
		return (write(2, "ft_calloc in parse_argv failed", 30), 0);
	while (i < data->cmds_count)
	{
		data->cmds[i] = ft_split(data->first_cmd[i], ' ');
		if (!data->cmds[i])
			return (write(2, "ft_split in parse_argv fail", 27), 0);
		if (!data->cmds[i][0])
		{
			free(data->cmds[i]);
			if (!build_empty_cmd(&data->cmds[i]))
				return (write(2, "build_empty_cmd in parse_argv fail", 34), 0);
		}
		i++;
	}
	data->cmds[i] = NULL;
	return (1);
}

/// @brief Extracts and prepares the system PATH directories.
/// @details Searches envp for the PATH variable, appends ":." to include
///          the current directory, and splits the result into an array
///          of directory paths. The resulting list is stored in data->paths
///          for later command lookup. Returns 0 if any memory allocation
///          fails or if PATH cannot be processed.
/// @param data Pointer to the main program state.
/// @return 1 on success, or 0 on failure.
static int	parse_paths(t_data *data)
{
	int		i;
	char	*full_path;

	if (data->envp == NULL)
		return (write(2, "envp is NULL", 12), 0);
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PATH=", 5))
			break ;
		else
			i++;
	}
	full_path = ft_strjoin(data->envp[i], ":.");
	if (!full_path)
		return (write(2, "ft_strjoin failed", 17), 0);
	if (!ft_strncmp(full_path, "PATH=", 5))
		data->paths = ft_split(full_path + 5, ':');
	else
		data->paths = ft_split(full_path, ':');
	if (!data->paths)
		return (free(full_path), write(2, "Split Failed", 12), 0);
	return (free(full_path), 1);
}

/// @brief Attempts to resolve a command name to an absolute executable path.
/// @details Iterates through all directories in paths and joins each one
///          with the command name. If an executable file is found (checked
///          using access with X_OK), the command name is replaced with its
///          full path. Temporary join strings are freed on each iteration.
///          If no match is found, the command is left unchanged.
/// @param cmds NUll terminated array of argv-style command arrays.
/// @param j Index of the command to check.
/// @param paths Null-terminated array of PATH directories.
/// @return 1 on success, or 0 if memory allocation for the join fails.
static int	path_check_one(char ***cmds, int j, char **paths)
{
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_path(paths[i], cmds[j][0]);
		if (!temp)
			return (write(2, "Strjoin_path Failed", 19), 0);
		if (!access(temp, X_OK))
		{
			free(cmds[j][0]);
			cmds[j][0] = temp;
			return (1);
		}
		free(temp);
		i++;
	}
	return (1);
}

/// @brief Resolves each command in the pipeline using the PATH directories.
/// @details Iterates through all parsed commands and attempts to replace
///          each command name with its full executable path using
///          path_check_one(). Commands that are already absolute paths or
///          empty are left unchanged. Stops and returns 0 if any join or
///          allocation fails.
/// @param cmds A NUll terminated array of argv-style command arrays.
/// @param paths A NULL-terminated array of directory path strings.
/// @param data Pointer to the main program state.
/// @return 1 on success, or 0 if a resolution step fails.
static int	path_check(char ***cmds, char **paths, t_data *data)
{
	int		j;

	j = 0;
	while (cmds[j])
	{
		if (data->first_cmd && data->first_cmd[j])
		{
			if (!path_check_one(cmds, j, paths))
				return (0);
		}
		j++;
	}
	return (1);
}

/// @brief Initializes and prepares the main program state.
/// @details Validates argument count, allocates and initializes the t_data
///          structure, parses all commands into argv-style arrays, extracts
///          PATH directories, and resolves each command using the PATH list.
///          On any failure, allocated resources are freed and NULL is returned.
/// @param argc Argument count from main().
/// @param argv Argument vector from main().
/// @param envp Environment variables passed to the program.
/// @return Pointer to an initialized t_data structure on success, or NULL on
///         failure.
t_data	*setup(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = init_datas(argc, argv, envp);
	if (!data)
		return (free_datas(data), NULL);
	if (!parse_argv(data))
		return (free_datas(data), NULL);
	if (!parse_paths(data))
		return (free_datas(data), NULL);
	if (!path_check(data->cmds, data->paths, data))
		return (free_datas(data), NULL);
	return (data);
}
