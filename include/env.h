/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:22:27 by willda-s          #+#    #+#             */
/*   Updated: 2025/06/30 15:00:53 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

typedef struct s_env
{
	char			*key; //HOME
	char			*value;// /home/lebroue
	struct s_env	*next; //On passe a la variable d'env d'apres 

}					t_env;

////////////ENV.C && LST_UTILS_ENV.C///////////

int					add_back_env(t_env **envd);
t_env				*ft_lstlast_env(t_env *envd);
void				free_lst_env(t_env **envd, bool ext, int errcode);
void				init_lst_env(t_env **envd, char **env);

void				print_lst_env(t_env *envd);
void				print_envp(char **envp);