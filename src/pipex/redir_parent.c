/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:01:54 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/17 14:33:58 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_stds(int input, int output, t_data *data)
{
	if (input != data->input_fd)
	{
		if (dup2(input, STDIN_FILENO) == -1)
			return (perror("Dup2 for STDIN failed"), EXIT_FAILURE);
		close(input);
	}
	if (output != data->output_fd)
	{
		if (dup2(output, STDOUT_FILENO) == -1)
			return (perror("Dup2 for STDOUT failed"), EXIT_FAILURE);
		close(output);
	}
	return (0);
}

static int	file_open_handle(int *fd, t_redir *temp, t_in_out type)
{
	if (*fd != 1)
		close(*fd);
	temp->fd = file_open(temp->file, type);
	if (temp->fd == -1)
		return (perror(temp->file), EXIT_FAILURE);
	*fd = temp->fd;
	return (0);
}

static	void	handle_heredoc_case(t_data *data, t_redir *temp)
{
	if (data->input_fd != 0)
		close(data->input_fd);
	data->input_fd = temp->fd;
}

int	handle_redir_parent(t_data *data)
{
	t_redir	*temp;
	int		input;
	int		output;
	int		result;

	input = data->input_fd;
	output = data->output_fd;
	temp = data->cmds->redir;
	while (temp)
	{
		if (temp->type == REDIR_APPEND)
			result = file_open_handle(&output, temp, APPEND);
		else if (temp->type == REDIR_OUT)
			result = file_open_handle(&output, temp, OUT);
		else if (temp->type == REDIR_IN)
			result = file_open_handle(&input, temp, IN);
		else if (temp->type == REDIR_HEREDOC)
			handle_heredoc_case(data, temp);
		if (result)
			return (result);
		temp = temp->next;
	}
	result = handle_stds(input, output, data);
	return (result);
}
