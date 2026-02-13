

#ifndef LISTS_H
# define LISTS_H

# include <stdlib.h>

typedef enum e_type
{
	PIPE,
	REDIR_OUT, // >
	REDIR_APPEND, // >>
	REDIR_IN, // <
	REDIR_HEREDOC, // <<
	WORD
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char			*file;
	t_type			type;
	struct s_redir	*next;
	int				fd;
}	t_redir;

typedef struct s_envp
{
	char			*string;
	char			*identifier;
	char			*value;
	int				has_value;
	int				exported;
	struct s_envp	*next;
}	t_envp;

typedef struct s_cmds
{
	char			*whole_cmd;
	char			**argv;
	int				argc;
	t_type			*type;
	t_redir			*redir;
	struct s_cmds	*next;
}	t_cmds;

t_token		*ft_token_last(t_token *token);
int			ft_token_size(t_token *token);
void		ft_token_delone(t_token *token);
void		ft_token_clear(t_token **token);
void		ft_token_addback(t_token **token, t_token *new);

t_redir		*ft_redir_last(t_redir *redir);
int			ft_redir_size(t_redir *redir);
void		ft_redir_clear(t_redir **redir);
void		ft_redir_delone(t_redir *redir);
void		ft_redir_addback(t_redir **redir, t_redir *new);

t_cmds		*ft_cmds_last(t_cmds *cmds);
void		ft_cmds_clear(t_cmds **cmds);
int			ft_cmds_size(t_cmds *cmds);
void		ft_cmds_delone(t_cmds *cmds);
void		ft_cmds_addback(t_cmds **cmds, t_cmds *new);

t_envp		*ft_t_envp_last(t_envp *envp);
void		ft_t_envp_clear(t_envp **envp);
int			ft_t_envp_size(t_envp *envp);
void		ft_t_envp_delone(t_envp *envp);
void		ft_t_envp_addback(t_envp **envp, t_envp *new);

typedef struct s_total_info
{
	t_token			*token;
	t_cmds			*cmds;
	t_envp			*our_envp;
	int				exit_code;
	int				stdin;
	int				stdout;
}	t_total_info;

#endif
