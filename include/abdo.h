
#ifndef ABDO_H
# define ABDO_H

#include "minishell.h"
#include <stdarg.h>


typedef struct s_env
{
	char			*string;
	char			*identifier;
	char			*value;
	int				has_value;
	int				exported;
	struct s_env	*next;
}	t_env;

void	sig_handler(int sig);
void	signal_setup(void);

int		env_size(t_env *env);
void	free_arr(char **arr, int i);
char	**change_to_arr(t_env *env);
int		word_count(char const *s);

char	*get_env_value(t_env *env, char *str);

int		builtin_unset(t_env **env, char *str);
int		builtin_export(t_env **env, int argc, char **argv);
int		builtin_cd(t_env **env, char *new_path);
int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_echo(char *env);
int		builtin_exit(char *env);


#endif
