/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 03:28:54 by hadia             #+#    #+#             */
/*   Updated: 2025/11/16 15:39:16 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "env.h"
# include "minishell.h"
# include "parsing.h"
# include <limits.h>
# include <stdbool.h>
# include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct s_pipe
{
	int	prev_fd;
	int	pipe_fd[2];
}		t_pipe;

///////////////////////////////////////////////////////
//////////////// APPLY_REDICRECTIONS //////////////////
///////////////////////////////////////////////////////

/*APLLY_REIRECTIONS_INPUT_OUTPUT*/
int		apply_redirections_input_output(t_cmd *cmd);

/*REDIR_OUT_OPEN_AND_DUP_CLOSE_SECURE*/
int		redir_out_open_and_dup_close_secure(t_redir *redir, t_redir_type type);

/*REDIR_IN_OPEN_AND_DUP_CLOSE_SECURE*/
int		redir_in_open_and_dup_close_secure(t_redir *redir, bool flag);

///////////////////////////////////////////////////////
///////////////////////// EXEC ////////////////////////
///////////////////////////////////////////////////////

/////////////////////////////////
///////////// EXEC //////////////
/////////////////////////////////

/*EXEC_CMD*/
int		exec_cmd(t_data *data, char *input);

/*EXECUTE_PIPELINE*/
int		execute_pipeline(t_data *data, t_cmd *curr, char *input, int ret);

/*FREE_ENVP*/
void	free_envp(char **envp);

/////////////////////////////////
////////// EXEC UTILS ///////////
/////////////////////////////////

/*IS_SINGLE_CMD*/
int		is_single_cmd(t_data *data);

/*IS_BUILTINS*/

int		is_builtins(char *cmd);

/*WAITING*/
int		waiting(pid_t pid, int status);

///////////////////////////////////////////////////////
/////////////////// GET PATH EXEC /////////////////////
///////////////////////////////////////////////////////

/////////////////////////////////
/////////// GET PATH ////////////
/////////////////////////////////

/*GET_PATH*/
char	*get_path(char **envp, char *argv_cmd, int *ret);

/*GET_PATH_IN_PATHS_LIST*/
char	*get_path_in_paths_list(char **paths, int *ret, char *buffer,
			char *argv_cmd);

/*GET_PATH_IN_PATHS_LIST UTILS : FREE_PATH_AND_RETURN*/
char	*free_paths_and_return(char *result, char **paths);

/*CHECK_IS_ACCESS_AND_IS_DIRECTORY*/
char	*check_is_access_and_is_directory(char *new_path, int *ret);

/*CHECK_IS_ACCESS_AND_IS_DIRECTORY UTILS : CHECK_IF_IS_DIRECTORY */
int		check_if_is_a_directory(const char *path);

/////////////////////////////////
// GET PATH HANDLE ACCESS CMD ///
/////////////////////////////////

/*HANDLE_ACCESS_CMD*/
char	*handle_access_cmd(char *argv_cmd, int *ret);

/*HANDLE_ACCESS_CMD UTILS : IF_NO_ARGV_CMD*/
char	*if_no_argv_cmd(int *ret);

/*HANDLE_ACCESS_CMD UTILS : STRDUP_ERROR_MESSAGE*/
char	*strdup_error_message(int *ret);

/*HANDLE_ACCESS_CMD UTILS : ACCESS_ERROR_MESSAGE*/
char	*access_error_message(const char *argv_cmd, int *ret);

/*HANDLE_ACCESS_CMD UTILS : DIRECTORY_ERROR_NESSAGE*/
char	*directory_error_messsage(const char *argv_cmd, int *ret);

///////////////////////////////////////////////////////
/////////////// GET PATH EXEC UTILS ///////////////////
///////////////////////////////////////////////////////

/*GET_PATH_IN_PATHS_LIST UTILS : FT_STRJOIN_CHECKER*/
int		ft_strjoin_checker(char *buffer, char *to_free, char **paths, int *ret);

/*GET_PATH UTILS : ENVP_SEARCH*/
char	*envp_search(char **envp);

/*GET_PATH UTILS : PATH_CHECK*/
int		path_check(char *path, int *ret);

/*GET_PATH_IN_PATHS_LIST UTILS : FT_STRJOIN_CHECKER UTILS : FT_FREE_TAB_STR*/
void	ft_free_tab_str(char **str);

///////////////////////////////////////////////////////
///////////// HANDLE CHILD PROCESS EXEC ///////////////
///////////////////////////////////////////////////////

/*HANDLE CHILD PROCESS*/
void	handle_child_process(t_data *data, t_cmd *curr, t_pipe *p, char *input);

/*HANDLE CHILD PROCESS UTILS : CHILD_PIPE_REDIR_DUP2_CLOSE_SECURE*/
int		child_pipe_redir_dup2_close_secure(t_cmd *curr, t_pipe *p);

/*HANDLE CHILD PROCESS UTILS : CHECK_FILE_POINTS*/
void	check_file_points(t_data *data, t_cmd *curr, int *ret);

/*HANDLE CHILD PROCESS UTILS : CHECK_COMMAND_PATH*/
void	check_command_path(t_cmd *curr, t_data *data, int *ret);

///////////////////////////////////////////////////////
///////////// HANDLE PARENT BUILTINS EXEC /////////////
///////////////////////////////////////////////////////

/*HANDLE_PARENT_BUILTINS*/
int		handle_parent_builtins(t_data *data, t_cmd *curr, char *input);

/*HANDLE_PARENT_BUILTINS UTILS : HANDLE_EXIT_BUILTIN*/
int		handle_exit_builtin(t_data *data, t_cmd *curr, char *input);

/*HANDLE_PARENT_BUILTINS UTILS : SAVE_STD_IN_OUT*/
int		save_std_in_out(int *saved_stdin, int *saved_stdout);

/*HANDLE_PARENT_BUILTINS UTILS : RESET_STD_IN_OUT*/
void	reset_std_in_out(int saved_stdin, int saved_stdout);

///////////////////////////////////////////////////////
///////////// HANDLE PARENT PROCESS EXEC //////////////
///////////////////////////////////////////////////////

/*HANDLE_PARENT_PROCESS*/
void	handle_parent_process(t_cmd **curr, t_pipe *p);

///////////////////////////////////////////////////////
//////////////// UPDATE ENVP EXEC UTILS ///////////////
///////////////////////////////////////////////////////

/*UPADTE_ENVP_FROM_LST_ENV_NODE*/
void	udpate_envp_from_lst_env_node(t_env *curr, char **envp, int i);

/*UPADTE_ENVP_FROM_LST_ENV_NODE UTILS : FT_STRJOIN_CHECKER_ENVP*/
int		ft_strjoin_checker_envp(char *buffer, char **envp, int i);

///////////////////////////////////////////////////////
/////////////////// UPDATE ENVP EXEC //////////////////
///////////////////////////////////////////////////////

/*UPDATE_ENVP*/
void	update_envp(t_data *data);

/*UPDATE_ENVP UTILS : BUILD_ENVP_ARRAY_FROM_LST_ENV*/
char	**build_envp_array_from_lst_env(t_env *env);

/*BUILD_ENVP_ARRAY_FROM_LST_ENV UTILS : FILL_ENVP_ARRAY_FROM_LST*/
void	fill_envp_array_from_lst(t_env *env, char **envp);

/*BUILD_ENVP_ARRAY_FROM_LST_ENV UTILS : COUNT_NODE*/
int		count_node(t_env *tmp);

#endif
