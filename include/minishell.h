/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:49:14 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:49:16 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include "../libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include "pipex.h"
# include "builtins.h"
# include "lists.h"
# include "haris.h"
# include "expand.h"

# define RED   "\001\033[1;31m\002"
# define RESET "\001\033[0m\002"

int				type_checker(t_type curr_type, t_type next_type, t_token *lst);
t_total_info	*init_total(char **envp, int exit);
char			*ft_strjoin_arg(char const *s1, char const *s2);
t_token			*parse_input(char *line);
t_token			*new_node(char *str, int len);
int				return_i(char *redir_file);
int				is_operator(char c);
int				copy_envp(t_total_info *total, char **envp);

int				get_cmds(t_total_info *total, t_token *lst);

#endif
