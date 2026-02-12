
#include "../include/pipex.h"

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

static int	handle_append_out(t_data *data, t_redir	*temp)
{
	if (temp->type == REDIR_APPEND
		|| temp->type == REDIR_OUT)
	{
		if (data->output_fd != 1)
			close(data->output_fd);
		if (temp->type == REDIR_APPEND)
			temp->fd = file_open(temp->file, APPEND);
		else
			temp->fd = file_open(temp->file, OUT);
		if (temp->fd == -1)
			return (perror(temp->file), EXIT_FAILURE);
		data->output_fd = temp->fd;
	}
	else
	{
		if (data->input_fd != 0)
			close(data->input_fd);
		temp->fd = file_open(temp->file, IN);
		if (temp->fd == -1)
			return (perror(temp->file), EXIT_FAILURE);
		data->input_fd = temp->fd;
	}
	return (EXIT_SUCCESS);
}

static int	stds_handler(t_data *data, int input, int output)
{
	if (input != data->input_fd)
	{
		if (dup2(data->input_fd, STDIN_FILENO) == -1)
			return (perror("Dup2 for STDIN failed"), EXIT_FAILURE);
		close(data->input_fd);
	}
	if (output != data->output_fd)
	{
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
			return (perror("Dup2 for STDOUT failed"), EXIT_FAILURE);
		close(data->output_fd);
	}
	return (EXIT_SUCCESS);
}

int	handle_redir_parent(t_data *data)
{
	t_redir	*temp;
	int		input;
	int		output;

	input = data->input_fd;
	output = data->output_fd;
	temp = data->cmds->redir;
	while (temp)
	{
		if (temp->type == REDIR_APPEND || temp->type == REDIR_OUT
			|| temp->type == REDIR_IN)
		{
			if (handle_append_out(data, temp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (temp->type == REDIR_HEREDOC)
		{
			if (data->input_fd != 0)
				close(data->input_fd);
			data->input_fd = temp->fd;
		}
		temp = temp->next;
	}
	return (stds_handler(data, input, output));
}
