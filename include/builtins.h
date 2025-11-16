/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:42:34 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/16 16:32:34 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libft/libft.h"
# include "env.h"
# include "minishell.h"
# include "parsing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

# define INT64_MAX_STR "9223372036854775807"
# define INT64_MIN_STR "9223372036854775808"

typedef struct s_cmd		t_cmd;
typedef struct s_data		t_data;
typedef struct s_env		t_env;
typedef enum e_redir_type	t_redir_type;
typedef struct s_redir		t_redir;
typedef struct s_token		t_token;
typedef struct s_env		t_env;
///////////////////////////////////////////////////////
////////////////////// EXEC BUILTINS //////////////////
///////////////////////////////////////////////////////

/*EXEC_BUILTINS*/
int							exec_builtins(t_cmd *cmd, t_data *data, char **env,
								char *input);

/*ft_exit_handle*/
int							ft_exit_handle(t_cmd *cmd, t_data *data, int status,
								char *input);

///////////////////////////////////////////////////////
////////////////////// BUILTINS ///////////////////////
///////////////////////////////////////////////////////

/////////////////////////////////
////////////// CD ///////////////
/////////////////////////////////

/*FT_CD*/
int							ft_cd(char **args);

/*CD_GET_PATH*/
char						*cd_get_path(char **args);

/////////////////////////////////
/////////// CD_UTILS ////////////
/////////////////////////////////

/*CHECK_IF_TO_MANY_ARGS*/
bool						check_if_to_many_arguments(char **args);

/*CHECK_PATH_LIMIT*/
bool						check_directory_path_size_limit(char *path,
								size_t limit);

/*CHECK_CHDIR_SECURE*/
bool						check_chdir(int ret);

/*CHECK_IF_PATH_IS_VALID*/
bool						check_path_is_valid(char *path, size_t limit);

/////////////////////////////////
///////////// ECHO //////////////
/////////////////////////////////

/*FT_ECHO*/
int							ft_echo(char **str);

/*COUNT_TAB*/
size_t						count_array_lines(char **str);

/////////////////////////////////
///////////// ENV ///////////////
/////////////////////////////////

/*ENV*/
int							ft_env(char **env);

/////////////////////////////////
///////////// EXIT //////////////
/////////////////////////////////

/*EXIT*/
int							ft_exit(char **args, t_data *data);

/*EXIT : ATOI_SECURE*/
int							ft_atoi_secure(const char *str);

/*EXIT : IS NUMBER*/
bool						is_valid_number(const char *str);

/////////////////////////////////
///////////EXIT_UTILS////////////
/////////////////////////////////

/*IS NUMBER_UTILS: SKIP WHITE SPACES*/
bool						skip_white_spaces(const char *str, int *i);

/*IS NUMBER_UTILS: GET_SIGNS*/
int							get_sign(const char *str, int *i);

/*IS NUMBER_UTILS: CHECK IF ONLY DIGITS*/
bool						check_if_only_digits(const char *str, int start);

/*IS NUMBER_UTILS: SKIP 0 AT BEGINING OF THE STRING*/
const char					*skip_zero_at_begining(const char *nb);

/*IS NUMBER_UTILS: CHECK LEN AND LIMITS OF LONG LONG INT*/
bool						check_len_and_limits(const char *nb, int sign);

/////////////////////////////////
///////////// EXPORT ////////////
/////////////////////////////////

/*FT_EXPORT*/
int							ft_export(char **args, char **env, t_data *data);

/*HANDLE_NO_ARG*/
int							handle_no_args(char **env);

/*PROCESS_SINGLE_ARG*/
int							process_single_arg(char *arg, t_data *data);

/*PROCESS_SINGLE_ARG UTILS :CHECK IF ARG IS CORRECT*/
bool						check_if_arg_is_correct(char *str);

/*PROCESS_SINGLE_ARG UTILS : ERROR MESSAGE*/
void						error_message(char *arg);

/////////////////////////////////
////////// EXPORT_UTILS /////////
/////////////////////////////////

/*ADD_OR_UPDATE_ENV*/
void						add_or_update_env(t_env **env, char *str);

/*ADD_OR_UPDATE_ENV UTILS : TRY_UPDATE_VALUE_IN_EXISTING_VARIABLE*/
bool						try_update_value_in_existing_variable(t_env *env,
								const char *key, char *value);

/*ADD_OR_UPDATE_ENV UTILS : ADD_NEW_VARIABLE_ENV_NODE*/
void						add_new_variable_env_node(t_env **env, char *key,
								char *value);

/////////////////////////////////
//////// EXPORT_UTILS_KEY ///////
/////////////////////////////////

/*SPLIT_VARIABLE_KEY_AND_VALUE*/
void						split_variable_key_and_value(const char *str,
								char **key_out, char **value_out);

/*SPLIT_VARIABLE_KEY_AND_VALUE UTILS : HANDLE_KEY_AND_VALUE*/
void						handle_key_and_value(const char *str, char *eq_pos,
								char **key_out, char **value_out);

/*SPLIT_VARIABLE_KEY_AND_VALUE UTILS : HANDLE_KEY_ONLY*/
void						handle_key_only(const char *str, char **key_out,
								char **value_out);

/////////////////////////////////
///////////// PWD ///////////////
/////////////////////////////////

/*FT_PWD*/
int							ft_pwd(void);

/////////////////////////////////
///////////// UNSET /////////////
/////////////////////////////////

/*FT_UNSET*/
int							ft_unset(char **args, char **env, t_data *data);

/*FT_UNSET UTILS : CHECK_IF_VARIABLE_KEY_IS_CORRECT*/
bool						check_if_variable_key_is_correct(char *str);

/*FT_UNSET UTILS : DELETE_ENV_NODE_VARIABLE*/
void						delete_env_node_variable(t_env **env_list,
								const char *key_to_del);

/*FT_UNSET UTILS : DELETE_ENVP_TAB_VARIABLE*/
void						delete_envp_tab_variable(char **envp,
								const char *key_to_del);

#endif
