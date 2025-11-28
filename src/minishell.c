/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:52:56 by hkonstan          #+#    #+#             */
/*   Updated: 2025/11/28 13:46:24 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ablud_split(line);
		//EXECUTION
		free(line);
	}
	return (0);
}
