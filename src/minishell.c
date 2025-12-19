
#include "minishell.h"

// valgrind -s --leak-check=full --show-leak-kinds=definite --track-fds=yes --log-file="valgrind-%p.log" ./minishell

volatile sig_atomic_t	g_signal;

static t_total_info	*init_total(void)
{
	t_total_info	*total;

	total = ft_calloc(1, sizeof(t_total_info));
	if (!total)
		return (write(2, "Mem alloc in init total failed", 30), NULL);
	total->cmds = NULL;
	total->token = NULL;
	return (total);
}
int	main(void)
{
	t_total_info	*total;
	char			*line;

	signal_setup();
	while (1)
	{
		total = init_total();
		if (!total)
			return (1);
		g_signal = 0;
		line = readline("Ourminishell>");
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
		if (!ft_strncmp(line, "exit", 5))
			return (free(line), 0);
		total->token = parse_input(line);
		if (!total->token)
			return (free(line), free(total), 0);
		total->cmds = get_cmds(total->token);
		if (!total->cmds)
			return (printf("fail cmd"), 1);
		free(line);
		// print_lst(total->token);
		// print_cmds(total->cmds);
		free_all(&total);
	}
	return (0);
}
