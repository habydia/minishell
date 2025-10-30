#ifndef BUILTINS_H
#define BUILTINS_H
#include "../libft/libft/libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

#define INT64_MAX_STR "9223372036854775807"
#define INT64_MIN_STR "9223372036854775808"

///////////////////////////////////////////////////////
////////////////////// BUILTINS ///////////////////////
///////////////////////////////////////////////////////

///////////////////////// PWD /////////////////////////
int		ft_pwd(void);

///////////////////////// ENV /////////////////////////
int		ft_env(char **env);

///////////////////////// EXIT /////////////////////////

/*EXIT*/
int	ft_exit(char **args, t_data *data);

/*ATOLL*/
long long ft_atoll(const char *str);

/*IS_NUMBER*/
bool isnumber(const char *str);

////////EXIT_IS_NUMBER_UTILS////////

/*SKIP WHITE SPACES*/
bool		skip_white_spaces(const char *str, int *i);

/*GET_SIGNS*/

int			get_sign(const char *str, int *i);

/*CHECK IF ONLY DIGITS*/

bool		check_if_only_digits(const char *str, int start);

/*SKIP 0 AT BEGINING OF THE STRING*/

const char	*skip_zero_at_begining(const char *nb);

/*CHECK LEN AND LIMITS OF LONG LONG INT*/

bool		check_len_and_limits(const char *nb, int sign);

///////////////////////// ECHO /////////////////////////

int			ft_echo(char **str);

////////////////////////// CD //////////////////////////

int			ft_cd(char **str);

///////////////////////// UNSET /////////////////////////

int			ft_unset(char **str, char **env);

///////////////////////// EXPORT /////////////////////////

int			ft_export(char **str, char **env);

///////////////////// EXEC BUILTINGS /////////////////////

int		exec_builtins(t_data *data, char **env, char *input);

/////////////////////////// FREE ///////////////////////////

// void		free_tab(char **str);

//////////////////////////////////////

// typedef struct s_data
// {
// 	char *input; //direct dans data ?
// 	char **str;
		//tableau du split modifie pour les quote de input ?? ou stocker dans parsing ?
// 	t_env	*env; //structure pour l'env avec char *key && char *value ??
// 	t_parsing *parsing;
		//structure qui contiendra la structure token ? ou juste appelez s_token ?
// 	s_data *next;
// }

#endif