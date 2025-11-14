/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:43:01 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/14 21:43:04 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_data	t_data;
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;

}						t_env;

typedef struct s_cmd	t_cmd;
typedef struct s_data
{
	char				**dst;
	t_env				*env;
	char				**envp;
	int					errcode;
	int					i;
	int					saved_stdin;
	int					saved_stdout;
	t_cmd				*cmds;
}						t_data;

///////////////////////////////////////////////////////
///////////////////////// ENV /////////////////////////
///////////////////////////////////////////////////////

/////////////////////////////////
////////// INIT_LST_ENV /////////
/////////////////////////////////

/*INIT_LST_ENV*/
void					init_lst_env(t_env **envd, char **env);

/*INIT_MINIMAL_LST_ENV*/
void					init_minimal_lst_env(t_env **envd);

/*INIT_MINIMAL_LST_ENV UTILS : PROCESS_MINIMUM_VAIRABLES*/
void					process_minimum_variables(t_env **envd,
							char *pwd_variable);

/////////////////////////////////
/////// INIT_LST_ENV UTILS //////
/////////////////////////////////

/*FREE_LST_ENV*/
void					free_lst_env(t_env **envd, bool ext, int errcode);

/*FT_LSTLAST_ENV*/
t_env					*ft_lstlast_env(t_env *envd);

/*ADD_BACK_ENV*/
int						add_back_env(t_env **envd);

/////////////////////////////////
//////// INIT_ENVP_ARRAY ////////
/////////////////////////////////

/*INIT_ENVP_ARRAY*/
void					init_envp_array(t_data *data);

/*INIT_ENVP_ARRAY UTILS : COUNT_LST_ENV_NODE*/
int						count_lst_env_node(t_data *data);

/*INIT_ENVP_ARRAY UTILS : FREE_ENVP_ARRAY_AT_INIT*/
void					free_envp_array_at_init(char **envp);

/*INIT_ENVP_ARRAY UTILS : FILL_ENVP_ARRAY*/
void					fill_envp_array(t_data *data);

/////////////////////////////////
/////// INIT_DATA_STRUCTURE /////
/////////////////////////////////

/*INIT_DATA*/
void					init_data(t_data *data, t_env **envd, char **dst);

////////////ENV.C && LST_UTILS_ENV.C///////////
void					init_data(t_data *data, t_env **envd, char **dst);
// void					init_envp_array(t_data *data);
int						add_back_env(t_env **envd);
t_env					*ft_lstlast_env(t_env *envd);
void					free_lst_env(t_env **envd, bool ext, int errcode);
void					init_lst_env(t_env **envd, char **env);

void					print_lst_env(t_env *envd);
void					print_envp(char **envp);

int						free_all(t_data *data, int errcode, char *str);

void					add_or_update_env(t_env **env, char *str);

#endif