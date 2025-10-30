/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:41:44 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/30 14:28:36 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "parsing.h"

//////////////////////////////////////////////
// Compte le nombre de node de la liste chainee envp du pars
//////////////////////////////////////////////
int count_node(t_env *tmp, int count)
{
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return(count);
}

int	ft_strjoin_checker_envp(char *buffer,char *to_free, char **paths)
{
	if (!buffer)
	{
		if(to_free)
			free(to_free);
		ft_free_tab_str(paths);
		// *ret = 1;
		return (0);
	}
	return (1);
}
//////////////////////////////////////////////
// Construire envp  en char ** depuis liste chaînée env
//////////////////////////////////////////////
char	**build_envp_tab_from_lst_env(t_env *env) // peux etre envyer un int *ret pour les strjoin
{
	int		count;
	t_env	*tmp;
	char	**envp;
	int		i;
	char	*key_equal;

	count = 0;
	tmp = env;
	i = 0;
	count = count_node(tmp, count); 
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		if (!ft_strjoin_checker_envp(envp[i], NULL, &tmp->key)) // a verifier pour la securisation du buffer checker
			return (NULL);
		key_equal = envp[i];
		envp[i] = ft_strjoin(key_equal, tmp->value);
		if(!ft_strjoin_checker_envp(key_equal, envp[i] , &tmp->key)) // a verifier pour la securisation du buffer checker
			return (NULL);
		free(key_equal);
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
	data->envp = build_envp_tab_from_lst_env(data->env);
}
