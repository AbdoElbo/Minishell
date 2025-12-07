
#include "minishell.h"

// valgrind -s --leak-check=full --show-leak-kinds=definite --track-fds=yes --log-file="valgrind-%p.log" ./minishell

volatile sig_atomic_t	g_signal;

void	sig_handler(int sig)
{
	g_signal = sig;
	if (g_signal == SIGINT)
		write(1, "\n", 1);
	// else if (sig == CTRL+D)
	// {
	// 	write(1, "\nexit\n", 6);
	// }
}

int	main(void)
{
	struct sigaction	sa;
	char				*line;
	t_token				*lst;

	g_signal = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	lst = NULL;
	while (!g_signal)
	{
		line = readline("Ourminishell>");
		if (line == NULL)
			break ;
		if (g_signal == SIGINT)
		{
			free(line);
			free_lst(lst);
			return (0);
		}
		if (*line != '\0')
			add_history(line);
		lst = parse_input(line);
		if (!lst)
			return (0);
		free(line);
	}
	return (0);
}
