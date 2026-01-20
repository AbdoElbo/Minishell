#ifndef BUILTINS_H
# define BUILTINS_H

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

int		env_size(t_env *env);
void	free_arr(char **arr, int i);
char	**change_to_arr(t_env *env);
int		word_count(char const *s);

int		get_identifier_and_value(char *str, char **identifier,
				char **value, int *has_value);
int		update_env(t_env **env);
t_env	*find_env(t_env *env, char *identifier);

//for printing the sorted export format
void	env_addback(t_env **env, t_env *new);
t_env	*env_last(t_env *env);
t_env	*create_node(char *iden, char *value, int has_value, int exported);
void	swap_nodes(t_env **sorted, t_env **prev, t_env **curr, int *swap);
void	sort_list(t_env **sorted);
int		create_sorted_env(t_env **sorted, t_env *env);
void	free_sorted_copy(t_env *sorted);
int		print_export_format(t_env *env);

int		builtin_export(t_env **env, int argc, char **argv);
int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_unset(t_env **env, int argc, char **argv);
char	*get_env_value(t_env *env, char *str);
int		builtin_cd(t_env **env, char *new_path);


#endif
