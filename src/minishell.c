
#include "minishell.h"

// valgrind -s --leak-check=full --show-leak-kinds=definite --track-fds=yes --log-file="valgrind-%p.log" ./minishell

volatile sig_atomic_t	g_signal;

int	main(void)
{

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
		lst = parse_input(line);
		if (!lst)
			return (free(line), 0);
		/*
		EXECUTION HERE
		*/
		free(line);
		free_lst(&lst);
	}
	return (0);
}
