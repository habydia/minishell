#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libft/libft/libft.h"
# include "env.h"
# include "minishell.h"
# include "parsing.h"
# include <readline/history.h>
# include <readline/readline.h>

# define INT64_MAX_STR "9223372036854775807"
# define INT64_MIN_STR "9223372036854775808"


///////////////////////////////////////////////////////
////////////////////// EXEC BUILTINS //////////////////
///////////////////////////////////////////////////////

int			exec_builtins(t_cmd *cmd, t_data *data, char **env, char *input);

///////////////////////////////////////////////////////
////////////////////// BUILTINS ///////////////////////
///////////////////////////////////////////////////////

/////////////////////////////////
////////////// CD ///////////////
/////////////////////////////////

/*FT_CD*/
int			ft_cd(char **args);

/*CD_GET_PATH*/
char	*cd_get_path(char **args);

/////////////////////////////////
/////////// CD_UTILS ////////////
/////////////////////////////////

/*CHECK_IF_TO_MANY_ARGS*/
bool	check_if_to_many_arguments(char **args);

/*CHECK_PATH_LIMIT*/
bool	check_directory_path_size_limit(char *path, size_t limit);

/*CHECK_CHDIR_SECURE*/
bool	check_chdir(int ret);

/*CHECK_IF_PATH_IS_CORRECT*/
bool	check_path_is_valid(char *path, size_t limit);

/////////////////////////////////
///////////// PWD ///////////////
/////////////////////////////////
int			ft_pwd(void);

/////////////////////////////////
///////////// ENV ///////////////
/////////////////////////////////

/*ENV*/
int			ft_env(char **env);

/////////////////////////////////
///////////// EXIT //////////////
/////////////////////////////////

/*EXIT*/
int			ft_exit(char **args, t_data *data);

/*EXIT UTILS : ATOLL*/
long long	ft_atoll(const char *str);

/*EXIT UTILS : IS NUMBER*/
bool		isnumber(const char *str);

/////////////////////////////////
///////////EXIT UTILS////////////
/////////////////////////////////

/*IS NUMBER_UTILS: SKIP WHITE SPACES*/
bool		skip_white_spaces(const char *str, int *i);

/*IS NUMBER_UTILS: GET_SIGNS*/

int			get_sign(const char *str, int *i);

/*IS NUMBER_UTILS: CHECK IF ONLY DIGITS*/

bool		check_if_only_digits(const char *str, int start);

/*IS NUMBER_UTILS: SKIP 0 AT BEGINING OF THE STRING*/

const char	*skip_zero_at_begining(const char *nb);

/*IS NUMBER_UTILS: CHECK LEN AND LIMITS OF LONG LONG INT*/

bool		check_len_and_limits(const char *nb, int sign);

/////////////////////////////////
///////////// ECHO //////////////
/////////////////////////////////

int			ft_echo(char **str);




/////////////////////////////////
///////////// UNSET /////////////
/////////////////////////////////

int			ft_unset(char **args, char **env, t_data *data);

/////////////////////////////////
///////////// EXPORT ////////////
/////////////////////////////////

int			ft_export(char **args, char **env, t_data *data);
void error_message(char *arg);


/*EXPORT_UTILS*/

void	add_or_update_env(t_env **env, char *str);


/*EXPORT_UTILS_KEY*/

void	handle_key_value(const char *str, char *eq_pos, char **key_out, char **value_out);

void	handle_key_only(const char *str, char **key_out, char **value_out);

void	split_key_value(const char *str, char **key_out, char **value_out);





/////////////////////////// FREE ///////////////////////////

// void		free_tab(char **str);

//////////////////////////////////////

// typedef struct s_data
// {
// 	char *input; //direct dans data ?
// 	char **str;
// tableau du split modifie pour les quote de input ?? ou stocker dans parsing ?
// 	t_env	*env; //structure pour l'env avec char *key && char *value ??
// 	t_parsing *parsing;
// structure qui contiendra la structure token ? ou juste appelez s_token ?
// 	s_data *next;
// }

#endif