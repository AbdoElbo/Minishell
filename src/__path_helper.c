
#include "minishell.h"


char	*ft_strjoin_arg(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	total_len;
	size_t	i;

	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) +2;
	new_string = malloc(total_len);
	if (new_string == NULL)
		return (NULL);
	if (s1)
		while (*s1)
			new_string[i++] = *s1++;
	if (i != 0)
		new_string[i++] = ' ';
	if (s2)
		while (*s2)
			new_string[i++] = *s2++;
	new_string[i] = '\0';
	return (new_string);
}
