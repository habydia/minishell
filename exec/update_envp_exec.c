/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:41:44 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/28 17:07:54 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "parsing.h"

//////////////////////////////////////////////
// Construire envp  en char ** depuis liste chaînée env
//////////////////////////////////////////////
char	**build_envp_from_lst_env(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	int		i;
	char	*tmp2;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		tmp2 = envp[i];
		envp[i] = ft_strjoin(tmp2, tmp->value);
		free(tmp2);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}


// //////////////////////////////////////////////
// // Mettre à jour envp dans data
// //////////////////////////////////////////////
void	update_envp(t_data *data)
{
	if (data->envp)
		free_envp(data->envp);
	data->envp = build_envp_from_lst_env(data->env);
}
