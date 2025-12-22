
#include "minishell.h"

static int	copy_envp(t_total_info *total, char **envp)
{
	int	i;

	(void)total;
	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	total->our_envp = ft_calloc(i + 1, sizeof(char *));
	if (!total->our_envp)
		return (write(2, "Mem alloc in expand failed", 26), 0);
	i = 0;
	while (envp[i])
	{
		total->our_envp[i] = ft_strdup(envp[i]);
		if (!(total->our_envp[i]))
			return(write(2, "Mem alloc in expand in strdup fail", 34), 0); 
		i++;
	}
	return (1);
}

static int	find_parameter(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < size)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((unsigned char)s1[i] != '=')
		return (1);
	return (0);
}

static int	find_d_quotes(t_token *lst)
{
	int i;
	
	while (lst)
	{
		i = 0;
		if (lst->type == WORD)
		{
			while (lst->value[i])
			{
				if (lst->value[i++] == '"')
					printf("hello");
			}
		}
	}
	return (1);
}
int	expand(t_total_info *total, char **envp)
{
	int	i;
	char abc[4] = "abc";
	t_token		*lst;

	lst = total->token;
	i = 0;
	if (!copy_envp(total, envp))
		return (0);
	while (find_d_quotes(lst))
	{
		while (total->our_envp[i])
		{
		// printf("\nline %i: %s\n", i + 1, total->our_envp[i]);
		if (find_parameter(total->our_envp[i], abc, ft_strlen(abc)))
			write(1, "found one \n", 11);
		}
	}
	return (1);
}
