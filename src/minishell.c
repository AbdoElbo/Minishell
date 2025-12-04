
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*lst;

	(void)argc;
	(void)argv;
	(void)envp;
	lst = NULL;
	while (1)
	{
		line = readline("ourminishell>");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);
		lst = parse_input(line);
		//PARSING
		//EXECUTION
		free(line);
	}
	return (0);
}
