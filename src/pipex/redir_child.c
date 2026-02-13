/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:06:54 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/13 16:32:46 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_stds(int input, int output, t_data *data)
{
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

static void	file_open_handle(int *fd, t_redir *temp, t_in_out type)
{
	if (*fd != 1)
		close(*fd);
	temp->fd = file_open(temp->file, type);
	if (temp->fd == -1)
		(perror(temp->file), _exit(EXIT_FAILURE));
	*fd = temp->fd;
}

void	handle_redirections(t_data *data)
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
			file_open_handle(&data->output_fd, temp, APPEND);
		else if (temp->type == REDIR_OUT)
			file_open_handle(&data->output_fd, temp, OUT);
		else if (temp->type == REDIR_IN)
			file_open_handle(&data->input_fd, temp, IN);
		else if (temp->type == REDIR_HEREDOC)
		{
			if (data->input_fd != 0)
				close(data->input_fd);
			data->input_fd = temp->fd;
		}
		temp = temp->next;
	}
	handle_stds(input, output, data);
}
