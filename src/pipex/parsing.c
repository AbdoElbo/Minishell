/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:12:04 by hariskon          #+#    #+#             */
/*   Updated: 2026/01/30 12:20:18 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// static int	parse_argv(t_data *data)
// {
// 	int		i;

// 	i = 0;
// 	data->cmds = ft_calloc((data->cmds_count + 1), sizeof(char **));
// 	if (data->cmds == NULL)
// 		return (write(2, "ft_calloc in parse_argv failed", 30), 0);
// 	while (i < data->cmds_count)
// 	{
// 		data->cmds[i] = ft_split(data->first_cmd[i], ' ');
// 		if (!data->cmds[i])
// 			return (write(2, "ft_split in parse_argv fail", 27), 0);
// 		if (!data->cmds[i][0])
// 		{
// 			free(data->cmds[i]);
// 			if (!build_empty_cmd(&data->cmds[i]))
// 				return (write(2, "build_empty_cmd in parse_argv fail", 34), 0);
// 		}
// 		i++;
// 	}
// 	data->cmds[i] = NULL;
// 	return (1);
// }

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

int	path_check_one(char **cmds, char **paths)
{
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_path(paths[i], cmds[0]);
		if (!temp)
			return (write(2, "Strjoin_path Failed", 19), 0);
		if (!access(temp, X_OK))
		{
			free(cmds[0]);
			cmds[0] = temp;
			return (1);
		}
		free(temp);
		i++;
	}
	return (1);
}

// static int	path_check(char ***cmds, char **paths, t_data *data)
// {
// 	int		j;

// 	j = 0;
// 	while (cmds[j])
// 	{
// 		if (data->cmds && data->cmds[0])
// 		{
// 			if (!path_check_one(cmds, j, paths))
// 				return (0);
// 		}
// 		j++;
// 	}
// 	return (1);
// }

t_data	*setup_datas(t_total_info *total)
{
	t_data	*data;

	data = init_datas(total);
	if (!data)
		return (free_datas(data), NULL);
	if (!parse_paths(data))
		return (free_datas(data), NULL);
	return (data);
}
