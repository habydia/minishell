/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:41:44 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_node(t_env *tmp)
{
	int	count;

	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	fill_envp_array_from_lst(t_env *env, char **envp)
{
	t_env	*curr;
	int		i;

	curr = env;
	i = 0;
	while (curr)
	{
		udpate_envp_from_lst_env_node(curr, envp, i);
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
}

char	**build_envp_array_from_lst_env(t_env *env)
{
	char	**envp;

	envp = ft_calloc(sizeof(char *), (count_node(env) + 1));
	if (!envp)
		return (NULL);
	fill_envp_array_from_lst(env, envp);
	return (envp);
}

void	update_envp(t_data *data)
{
	if (data->envp)
		free_envp(data->envp);
	data->envp = build_envp_array_from_lst_env(data->env);
}
