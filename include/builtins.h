#ifndef BUILTINS_H
# define BUILTINS_H

# include "lists.h"
# include "minishell.h"
# include <stdarg.h>

int		env_size(t_envp *env);
// void	free_arr(char **arr, int i);
char	**change_to_arr(t_envp *env);
int		word_count(char const *s);

int		get_identifier_and_value(char *str, char **identifier,
			char **value, int *has_value);
// int		update_env(t_envp **env);
t_envp	*find_env(t_envp *env, char *identifier);

//for printing the sorted export format
void	env_addback(t_envp **env, t_envp *new);
t_envp	*env_last(t_envp *env);
t_envp	*create_node_sorted(char *iden, char *value, int has_value, int exported);
void	swap_nodes(t_envp **sorted, t_envp **prev, t_envp **curr, int *swap);
void	sort_list(t_envp **sorted);
int		create_sorted_env(t_envp **sorted, t_envp *env);
void	free_sorted_copy(t_envp *sorted);
int		print_export_format(t_envp *env);

int		builtin_cd(t_envp **env, int argc, char **argv);
int		builtin_echo(char **strings);
int		builtin_exit(int argc, char **argv, t_total_info *total);
int		builtin_export(t_envp **env, int argc, char **argv);
int		builtin_pwd(void);
int		builtin_env(int argc, char **argv, t_envp **env);
int		builtin_unset(t_envp **env, int argc, char **argv);

int		is_builtin(t_data *data);
int		call_builtins(t_data *data, t_total_info *total);

#endif
