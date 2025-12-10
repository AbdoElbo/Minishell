
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
		if (!ft_strncmp(line, "exit", 5))
			return (free(line), 0);
		lst = parse_input(line);
		if (!lst)
			return (free(line), 0);
		get_cmds(lst);
		free(line);
	}
	return (0);
}
