/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:12:51 by hariskon          #+#    #+#             */
/*   Updated: 2026/01/27 21:06:33 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/// @brief Reads here_doc input from stdin into an internal pipe.
/// @details Repeatedly reads lines from stdin until the delimiter string
///          is encountered. All intermediate lines are written to the pipe,
///          whose read end becomes the new input_fd for the pipeline.
///          On failure, prints an error and leaves data unchanged.
/// @param data Pointer to the main program state (uses argv[2] as delimiter).
/// @return 1 on success, or 0 if pipe creation or input reading fails.
int	read_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*s;
	char	*delimiter;

	delimiter = redir->file;
	if (!delimiter)
		return (write(2, "Invalid delimiter", 17), 0);
	if (pipe(pipefd) < 0)
		return (perror("Pipe failed"), 0);
	s = get_next_line(0);
	if (!s)
		return (close_pipefd(pipefd), write(2, "GNL Fail", 8), 0);
	while (ft_strncmp(s, delimiter, ft_strlen(delimiter)))
	{
		write(pipefd[1], s, ft_strlen(s));
		free(s);
		s = get_next_line(0);
		if (!s)
			return (close_pipefd(pipefd), free(s), write(2, "GNL Fail", 8), 0);
	}
	free (s);
	get_next_line(-1);
	close(pipefd[1]);
	redir->fd = pipefd[0];
	return (1);
}

int	argc_check(char **argv, int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc <= 5)
			return (write(2, "Wrong input, put more arguments\n", 32), 0);
	}
	else
		if (argc <= 4)
			return (write(2, "Wrong input, put more arguments\n", 32), 0);
	return (1);
}

/// @brief Constructs a fallback command array containing a single empty string.
/// @details Allocates a two-element argv-style array and sets its first
///          element to an empty string. Used when a command input is empty
///          or whitespace-only to ensure consistent downstream handling.
/// @param cmds Address of the command slot to replace.
/// @return 1 on success, or 0 if allocation fails.
int	build_empty_cmd(char ***cmds)
{
	char	**array;

	array = ft_calloc(2, sizeof(char *));
	if (!array)
		return (0);
	array[0] = ft_strdup("");
	if (!array[0])
		return (free(array), 0);
	*cmds = array;
	return (1);
}

/// @brief Joins a directory path and a command name into a single path string.
/// @details Allocates a new string containing s1, a '/', and s2. If s2 is
///          empty or NULL, returns an allocated empty string. Intended for
///          PATH resolution where s1 is a directory and s2 is the command.
///          The caller is responsible for freeing the returned string.
/// @param s1 Directory path prefix.
/// @param s2 Command name to append.
/// @return A newly allocated joined string on success, or NULL on failure.
char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	total_len;
	size_t	i;

	i = 0;
	if (!s2 || *s2 == '\0')
	{
		new_string = ft_strdup("");
		if (!new_string)
			return (NULL);
		return (new_string);
	}
	total_len = ft_strlen(s1) + ft_strlen(s2) + 2;
	new_string = ft_calloc(sizeof(char), total_len);
	if (new_string == NULL)
		return (NULL);
	if (s1)
		while (*s1)
			new_string[i++] = *(s1++);
	new_string[i++] = '/';
	if (s2)
		while (*s2)
			new_string[i++] = *(s2++);
	new_string[i] = '\0';
	return (new_string);
}

/// @brief Waits for all child processes and frees program resources.
/// @details Iterates through the stored PIDs, calling waitpid() for each
///          child in order. The exit status of the last child is extracted
///          according to POSIX rules: normal exit returns its exit code,
///          signal termination returns 128 + signal number, and unexpected
///          cases default to 1. After all waits complete, the function frees
///          all allocated data structures.
/// @param data Pointer to the main program state containing child PIDs.
/// @return The exit code of the last command in the pipeline.
int	pid_wait_and_free(t_data *data)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	while (data->pids[i])
	{
		if (waitpid(data->pids[i], &status, 0) > 0)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
			else
				exit_code = 1;
		}
		i++;
	}
	free_datas(data);
	return (exit_code);
}

/// @brief Allocates and initializes the main program state structure.
/// @details Stores argc, argv, and envp, determines the number of pipeline
///          commands, and sets the starting position of the command strings
///          (adjusting for here_doc mode when present). Allocates the PID
///          array used to track child processes. Other fields are initialized
///          to NULL and populated later during setup.
/// @param argc Argument count from main().
/// @param argv Argument vector from main().
/// @param envp Environment variables passed to the program.
/// @return A pointer to a fully initialized t_data structure, or NULL on
///         allocation failure.
t_data	*init_datas(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->cmds = NULL;
	data->paths = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		data->cmds_count = argc - 4;
		data->first_cmd = argv + 3;
	}
	else
	{
		data->cmds_count = (argc - 3);
		data->first_cmd = argv + 2;
	}
	data->pids = ft_calloc(data->cmds_count + 1, sizeof(pid_t));
	if (!data->pids)
		return (NULL);
	return (data);
}
