
#include "minishell.h"

volatile sig_atomic_t	g_signal;

static void	sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	signal_setup(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	rl_catch_signals = 0;
}

static int	handle_line(t_total_info **total, char *line, int *exit_code)
{
	if (!*line || g_signal)
		return (free(line), 0);
	add_history(line);
	(*total)->token = parse_input(line);
	if (!(*total)->token)
		return ((*exit_code) = 2, free(line), 0);
	if (!get_cmds(*total, (*total)->token))
		return (free(line), 0);
	if (!expand(*total))
		return (free(line), 0);
	*exit_code = pipex(*total);
	free(line);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_total_info	*total;
	char			*line;
	char			**envp_a;
	int				exit_code;

	(void)argv;
	(void)argc;
	envp_a = envp;
	exit_code = 0;
	signal_setup();
	while (1)
	{
		total = init_total(envp_a, exit_code);
		if (!total)
			return (free_all(&total), errno); //maybe returning 1 is the correct return!
		g_signal = 0;
		// line = readline(RED"Minishell$ "RESET); //this is our line
		//the code bellow is needed for the tester
		if (isatty(STDIN_FILENO))
			line = readline(RED"Minishell$ "RESET);
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (line)
			{
				char *tmp = ft_strtrim(line, "\n");
				free(line);
				line = tmp;
			}
		}
		//the code above is needed for the tester.
		if (!line)
			break ;
		if (!handle_line(&total, line, &exit_code))
			return (free_all(&total), exit_code);
		// print_cmds(total->cmds);
		envp_a = change_to_arr(total->our_envp);
		free_all(&total);
	}
	return (exit_code);
}
