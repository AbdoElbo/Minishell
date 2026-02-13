/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:12:51 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/13 17:47:21 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/builtins.h"

static void	read_heredoc_helper(int pipefd[2], char **s)
{
	write(pipefd[1], *s, ft_strlen(*s));
	free(*s);
	*s = NULL;
	write(1, "> ", 2);
	*s = get_next_line(0);
}

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
	write(1, "> ", 2);
	s = get_next_line(0);
	if (!s)
		return (close_pipefd(pipefd), write(2, "GNL Fail", 8), 0);
	while (ft_strncmp(s, delimiter, ft_strlen(delimiter)) != 0
		|| s[ft_strlen(delimiter)] != '\n')
	{
		read_heredoc_helper(pipefd, &s);
		if (!s)
			break ;
	}
	free(s);
	get_next_line(-1);
	close(pipefd[1]);
	redir->fd = pipefd[0];
	return (1);
}

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

int	pid_wait_and_free(t_data *data)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
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

t_data	*init_datas(t_total_info *total)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->cmds_count = ft_cmds_size(total->cmds);
	data->cmds = total->cmds;
	data->envp_list = total->our_envp;
	data->input_fd = 0;
	data->output_fd = 1;
	data->envp_arr = change_to_arr(data->envp_list);
	if (!data->envp_arr)
		return (free(data), NULL);
	data->pids = ft_calloc(data->cmds_count + 1, sizeof(pid_t));
	if (!data->pids)
		return (NULL);
	return (data);
}
