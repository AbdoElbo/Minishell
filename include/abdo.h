
#ifndef ABDO_H
# define ABDO_H

#include "minishell.h"
#include <stdarg.h>

typedef struct s_env
{
	char			*string;
	struct s_env	*next;
}	t_env;

void	sig_handler(int sig);
void	signal_setup(void);

int		builtin_cd(t_env **env);
int		builtin_pwd(t_env **env);
int		builtin_env(t_env **env);
int		builtin_unset(t_env **env);
int		builtin_echo(const char *env);
int		builtin_export(char *env);
int		builtin_exit(char *env);


#endif
