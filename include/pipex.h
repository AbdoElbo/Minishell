/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:15:03 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/12 21:03:22 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include "lists.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

enum	e_in_out
{
	IN,
	OUT,
	APPEND,
};

typedef struct s_data
{
	t_cmds	*cmds;
	char	**paths;
	char	**envp_arr;
	t_envp	*envp_list;
	int		pipefd[2];
	int		input_fd;
	int		output_fd;
	int		cmds_count;
	pid_t	*pids;
}	t_data;

void	handle_redirections(t_data *data);
int		handle_redir_parent(t_data *data);
int		file_open(char *filename, enum e_in_out in_out);
int		path_check_one(char **cmds, char **paths);
int		pipex(t_total_info *total);
int		read_heredoc(t_redir *redir);
t_data	*setup_datas(t_total_info *data);
t_data	*init_datas(t_total_info *total);
char	*ft_strjoin_path(char const *s1, char const *s2);
void	free_datas(t_data *data);
void	close_pipefd(int pipefd[2]);
int		pid_wait_and_free(t_data *data);
void	child_exec_error(t_data *data);
int		restore_parent_stdio(t_total_info *total);
#endif
