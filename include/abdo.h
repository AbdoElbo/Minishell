
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

int		env_size(t_env *env);
void	free_arr(char **arr, int i);
char	**change_to_arr(t_env *env);
int		word_count(char const *s);

char	*get_env_value(t_env *env, char *str);
int		change_old_path(t_env **env, char *current_pwd);
int		update_new_path(t_env **env);
int		rollback_env(t_env **env, char **old, char **pwd);
int		builtin_cd(t_env **env);

int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_unset(t_env **env);
int		builtin_echo(const char *env);
int		builtin_export(char *env);
int		builtin_exit(char *env);


#endif
