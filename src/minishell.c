
#include "minishell.h"

// valgrind -s --leak-check=full --show-leak-kinds=definite --track-fds=yes --log-file="valgrind-%p.log" ./minishell

int	main(void)
{
	struct sigaction	sa;
	char				*line;
	t_token				*lst;
	t_cmds				*cmds;

	lst = NULL;
	while (1)
	{
		line = readline("Ourminishell>");
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
