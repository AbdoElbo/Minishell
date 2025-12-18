
#include "minishell.h"

// valgrind -s --leak-check=full --show-leak-kinds=definite --track-fds=yes --log-file="valgrind-%p.log" ./minishell

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT)
	{
		write(1, "\nhello\n", 8);
		exit(EXIT_SUCCESS);
	}
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

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	lst = NULL;
	while (1)
	{
		line = readline("Ourminishell>");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);
		lst = parse_input(line);
		if (!lst)
			return (0);
		free(line);
	}
	return (0);
}
