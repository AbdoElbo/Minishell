
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("ourminishell>");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);
		printf("%s\n", line);
		//PARSING
		//EXECUTION
		free(line);
	}
	return (0);
}
