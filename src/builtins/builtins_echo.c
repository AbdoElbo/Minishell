#include "builtins.h"

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
		if (argv[i + 1])
			printf(" ");
		else if (!argv[i + 1] && !no_nl)
			printf("\n");
		i++;
	}
}

int	builtin_echo(char **strings)
{
	int	i;
	int	no_nl;

	i = 1;
	no_nl = 0;
	while (strings[i] && newline_check(strings[i]))
	{
		no_nl = 1;
		i++;
	}
	print_strings(strings, no_nl, i);
	return (EXIT_SUCCESS);
}
