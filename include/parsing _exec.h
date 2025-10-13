#ifndef PARSING_H
#define PARSING_H

#include "../includes/env.h"
#include <stdbool.h>
#include "../libft/libft.h"


typedef enum s_type
{
	NUL,
	WORD = 1,
	PIPE = 1 << 1,
	HEREDOC = 1 << 2,
	REDIR_APPEND = 1 << 3,
	REDIR_TRUNC = 1 << 4,
	REDIR_IN = 1 << 5,
	COMMANDS = 1 << 6,
	ARGS = 1 << 7,
	BUILTINS = 1 << 8,
	TARGETS = 1 << 9,
	REDIR = REDIR_IN | HEREDOC | REDIR_APPEND | REDIR_TRUNC,
}					t_type;

typedef struct s_redir
{
	t_type			token;
	char			*filename;
	char			*delimiter;
	struct s_redir	*next;
}					t_redir;

typedef struct s_exec
{
	char			**cmd;
	char			*path;
	int				fd_in;
	int				fd_out;
	struct s_redir	*redir;
	struct s_exec	*next;
}					t_exec;

typedef struct s_pars
{
	t_type			type;
	char			*word;
	struct s_pars	*next;
}					t_pars;

typedef struct s_data
{
	char			**dst;
	t_env			*env;
	t_pars			*pars;
	t_exec			*exec;
	char			**envp;
	int				errcode;
	int				i;
}					t_data;

/////////////SPLIT_QUOTES.C/////////////////////

char				**ft_split_with_quotes(char const *s, char c);

////////////LST_UTILS_PARS.C///////////////////

int					add_back_pars(t_pars **pars);

t_pars				*ft_lstlast_pars(t_pars *pars);

void				free_lst_pars(t_pars **pars);

void				print_lst_pars(t_pars *pars);

///////////INIT_DATA////////////////////

void				init_data(t_data *data, t_env **envd, char **dst);

///////////INIT_LST_EXEC.C && LST_UTILS_EXEC.C////////////////////

void				init_lst_exec(t_data *data);

t_exec				*ft_lstlast_exec(t_exec *exec);

int					add_back_exec(t_exec **exec);

void				print_lst_exec(t_exec *exec);

void				free_lst_exec(t_exec **exec);

//////////INIT_REDIR///////////////

t_redir				*ft_lstlast_redir(t_redir *redir);

int					add_back_redir(t_redir **redir);

void				free_lst_redir(t_redir **redir);

///////////////FUNCTIONS_FREE.C/////////////////////

int					free_all(t_data *data, int errcode, char *str);

void				free_tab(char **dst);

////////////////////TYPE.C && TYPE_UTILS.C/////////////////

void				token_main(t_data *data);

void				is_builtins(t_pars **tmp);

bool				is_redirection(t_pars **tmp);

////////////////EXPANDF.C  && EXPAND_UTILS.C////////////////////

char				*get_env_value(t_env *envd, char *key);

int					is_var_char(char c);

void				expand_exec_list(t_data *data);

////////////////INIT_FILENAME.C//////////////////////////

void				init_lst_redir(t_exec **exec, t_pars *pars, t_data *data);

////////////////SCRATCH_NODE.C////////////////////////////

void				remove_empty_line(t_data *data);

void				init_envp(t_data *data);

#endif
