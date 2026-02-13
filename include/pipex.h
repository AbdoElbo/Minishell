/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:15:03 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/12 14:44:01 by aelbouaz         ###   ########.fr       */
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

int		path_check_one(char **cmds, char **paths);
int		pipex(t_total_info *total);
int		read_heredoc(t_redir *redir);
t_data	*setup_datas(t_total_info *data);
t_data	*init_datas(t_total_info *total);
int		build_empty_cmd(char ***cmds);
char	*ft_strjoin_path(char const *s1, char const *s2);
void	free_datas(t_data *data);
void	close_pipefd(int pipefd[2]);
int		argc_check(char **argv, int argc);
int		pid_wait_and_free(t_data *data);
void	child_exec_error(t_data *data);
#endif
