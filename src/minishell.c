
#include "minishell.h"

volatile sig_atomic_t	g_signal;

t_envp	*new_envp_node(char *str)
{
	t_envp	*new_envp;

	new_envp = ft_calloc(1, sizeof(t_envp));
	if (!new_envp)
		return (write(2, "Memaloc 2 fail new_envp", 23), NULL);
	new_envp->string = ft_strdup(str);
	if (!new_envp->string)
		return (write(2, "Memaloc 2 fail new_envp", 23), free(new_envp), NULL);
	new_envp->next = NULL;
	return (new_envp);
}

static int	update_env(t_envp **env)
{
	t_envp	*temp;
	char	*identifier;
	char	*value;
	int		has_value;

	temp = *env;
	while (temp)
	{
		identifier = NULL;
		value = NULL;
		has_value = 0;
		if (!get_identifier_and_value(temp->string, &identifier
				, &value, &has_value))
			return (free(identifier), free(value), 0);
		temp->identifier = identifier;
		temp->value = value;
		temp->has_value = has_value;
		temp->exported = 1;
		temp = temp->next;
	}
	return (1);
}

static int	copy_envp(t_total_info *total, char **envp)
{
	int		i;
	t_envp	*new_envp;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		new_envp = new_envp_node(envp[i]);
		if (!new_envp)
			return (0);
		ft_t_envp_addback(&total->our_envp, new_envp);
		i++;
	}
	if (!update_env(&total->our_envp))
		return (0);
	return (1);
}

static t_total_info	*init_total(char **envp, int exit)
{
	t_total_info	*total;

	total = ft_calloc(1, sizeof(t_total_info));
	if (!total)
		return (write(2, "1st Mem alloc in init total failed", 34), NULL);
	total->stdin = dup(STDIN_FILENO);
	if (total->stdin == -1)
		return (close(total->stdin), perror("dup"), free(total), NULL);
	total->stdout = dup(STDOUT_FILENO);
	if (total->stdout == -1)
		return (close(total->stdout), perror("dup"), free(total), NULL);
	total->cmds = NULL;
	total->token = NULL;
	total->exit_code = exit;
	if (!copy_envp(total, envp))
		return (write(2, "2 Mem alloc in init_t fail", 26), free(total), NULL);
	return (total);
}

int	main(int argc, char **argv, char **envp)
{
	t_total_info	*total;
	char			*line;
	int				exit;

	(void)argv;
	(void)argc;
	exit = 0;
	signal_setup();
	while (1)
	{
		total = init_total(envp, exit);
		if (!total)
			return (free_all(&total), errno); //maybe returning 1 is the correct return!
		g_signal = 0;
		line = readline(RED"Minishell$ "RESET);
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (g_signal)
		{
			free(line);
			continue ;
		}
		if (*line != '\0')
			add_history(line);
		// if (!ft_strncmp(line, "exit", 5))
		// 	return (free(line), free_all(&total), 0);
		total->token = parse_input(line);
		if (!total->token)
			return (free(line), free_all(&total), 0);
		// print_lst(total->token);
		if (!get_cmds(total, total->token))
			return (free_all(&total), free(line), 1);
		// print_cmds(total->cmds);
		if (!expand(total))
			return (free(line), free_all(&total), 0);
		// print_cmds(total->cmds);
		exit = pipex(total);
		free(line);
		// check_our_envp(total->our_envp, envp);
		// print_lst(total->token);
		// print_cmds(total->cmds);
		free_all(&total);
	}
	return (exit);
}
