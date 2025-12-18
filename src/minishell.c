
#include "minishell.h"

// valgrind -s --leak-check=full --show-leak-kinds=definite --track-fds=yes --log-file="valgrind-%p.log" ./minishell

volatile sig_atomic_t	g_signal;

int	main(void)
{
	t_cmds *cmds;
	
	char	*line;
	t_token	*lst;

	lst = NULL;
	signal_setup();
	while (1)
	{
		g_signal = 0;
		line = readline("Ourminishell>");
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		if (g_signal)
		{
			free(line);
			continue;
		}
		if (*line != '\0')
			add_history(line);
		else
			continue ;
		if (!ft_strncmp(line, "exit", 5))
			return (free(line), 0);
		lst = parse_input(line);
		if (!lst)
			return (free(line), 0);
		cmds = get_cmds(lst);
		free(line);
		if (!cmds)
			return (printf("fail cmd"), 1);
		print_cmds(cmds);
	}
	return (0);
}
