#include "builtins.h"

// returns 1 if the string is variation of :
// -n or -nnnn or -nnnnnnnnn...
// returns 0 if the string should be treated as a string (no newline)
static int	newline_check(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	print_strings(char **argv, int no_nl, int i)
{
	if (!argv[i])
	{
		if (!no_nl)
			printf("\n");
		return ;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1]) // there's another string after the one we printed a line ago
			printf(" "); // we print one space
		else if (!argv[i + 1] && !no_nl)
			printf("\n");
		i++;
	}
}

int	builtin_echo(char *env, int argc, char **argv)
{
	int	i;
	int	no_nl;

	(void)env;
	(void)argc;
	i = 1;
	no_nl = 0;
	while (argv[i] && newline_check(argv[i]))
	{
		no_nl = 1;
		i++; // im using the index i to start printing from it in the next func
	}
	print_strings(argv, no_nl, i);
	return (EXIT_SUCCESS);
}


