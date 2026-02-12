
#include "../include/pipex.h"

static void	handle_append_out(t_data *data, t_redir	*temp)
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
			(perror(temp->file), _exit(EXIT_FAILURE));
		data->output_fd = temp->fd;
	}
	else
	{
		if (data->input_fd != 0)
			close(data->input_fd);
		temp->fd = file_open(temp->file, IN);
		if (temp->fd == -1)
			(perror(temp->file), _exit(EXIT_FAILURE));
		data->input_fd = temp->fd;
	}
}

static void	stds_handler(t_data *data, int input, int output)
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
		if (temp->type == REDIR_APPEND || temp->type == REDIR_OUT
			|| temp->type == REDIR_IN)
			handle_append_out(data, temp);
		else if (temp->type == REDIR_HEREDOC)
		{
			if (data->input_fd != 0)
				close(data->input_fd);
			data->input_fd = temp->fd;
		}
		temp = temp->next;
	}
	stds_handler(data, input, output);
}
