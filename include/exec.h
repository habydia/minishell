#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <limits.h>
#include <sys/stat.h>

typedef struct s_pipe
{
	int	prev_fd;
	int	pipe_fd[2];
}		t_pipe;

void	print_lst_env(t_env *envd);
void	print_envp(char **envp);

char	*envp_search(char **envp);
int		path_check(char *path, int *ret);

char	*ft_strdup(const char *s);

// char	**build_argv(t_pars *pars);
// char	**build_envp_from_lst_env(t_env *env);
void	update_envp(t_data *data);
int		exec_cmd(t_data *data, char *input);

void	reset_std_in_out(t_data *data);

void	save_std_in_out(t_data *data);

void	process_env_node(t_env *curr, char **envp, int i);
/////////////////////////////////////

////////APPLY_REDICRECTIONS/////////////////

int	apply_redirections_input_output(t_cmd *cmd);

int	redir_out_open_and_dup_close_secure(t_redir *redir, t_redir_type type);

int		redir_in_open_and_dup_close_secure(t_redir *redir, bool flag);

////////EXEC_UTILS////////////////////

int		is_single_cmd(t_data *data);

int	is_builtins(char *cmd); // a renormer

// void	save_std_in_out(t_data *data);

void	reset_std_in_out(t_data *data);

int		waiting(pid_t pid, int status);

///////////GET_PATH_EXEC////////////////////

char	*envp_search(char **envp);

int		path_check(char *path, int *ret);

int		ft_strjoin_checker(char *buffer, char *to_free, char **paths, int *ret);

char	*get_path_in_paths_list(char **paths, int *ret, char *buffer,
			char *argv_cmd);

char	*get_path(char **envp, char *argv_cmd, int *ret);

int	check_if_is_a_directory(const char *path);


/////////HANDLE_PARENT_BUILTINS//////////////////////

int	handle_parent_builtins(t_data *data, t_cmd *curr, char *input);

/////////////HANDLE_CHILD_PROCESS/////////////////////////////////

void handle_child_process(t_data *data, t_cmd *curr, t_pipe *p, char *input);

void check_command_path(t_cmd *curr, t_data *data, int *ret);

int child_pipe_redirection_dup2_close_secure(t_cmd *curr, t_pipe *p);

////////HANDLE_PARENT_PROCESS////////////////////////////////////////

void handle_parent_process(t_cmd **curr, t_pipe *p);


/////////////////////////////GET-PATH////////////////////////////////

char	*get_path_in_paths_list(char **paths, int *ret, char *buffer,char *argv_cmd);


char	*get_path(char **envp, char *argv_cmd, int *ret);

char *check_is_access_and_is_directory(char *new_path, int *ret);

char *handle_access_cmd(char *argv_cmd, int *ret);




//////////////////////GET_PATH_UTILS///////////////////////////////////

int	ft_strjoin_checker(char *buffer, char *to_free, char **paths, int *ret);

int	path_check(char *path, int *ret);

char	*envp_search(char **envp);


void	ft_free_tab_str(char **str);

// #include "env.h"
////PATH UTILS///
// void	ft_free_tab_str(char **str);

// char	*envp_search(char **envp);

// int	path_check(char *path, int *ret);

// char	*strjoin_check_error(char *str);

// //GET PATH///////

// char	*get_path_in_paths_list(char **paths, int *ret, char *buffer,
// char *argv_cmd);

// char	*get_path(char **envp, char *argv_cmd, int *ret);

//
//////////////////////////////////////////////////////////////////////////////////////////////

// char *get_unique_heredoc_path(void);

// char *handle_heredoc(char *delimiter);

// void apply_redirections(t_exec *exec);

// char **build_argv(t_pars *pars);

// void free_argv(char **argv);

// char **build_envp_from_lst_env(t_env *env);

// void free_envp(char **envp);

// void update_envp(t_data *data);

// int exec_cmd(t_data *data);

#endif
