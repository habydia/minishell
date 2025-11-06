/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:41:44 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/06 23:53:10 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "parsing.h"

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

void	fill_envp_tab_from_lst(t_env *env, char **envp)
{
	t_env	*curr;
	int		i;

	curr = env;
	i = 0;
	while (curr)
	{
		process_env_node(curr, envp, i);
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
}

char	**build_envp_tab_from_lst_env(t_env *env)
{
	char	**envp;

	envp = ft_calloc(sizeof(char *), (count_node(env) + 1));
	if (!envp)
		return (NULL);
	fill_envp_tab_from_lst(env, envp);
	return (envp);
}

void	update_envp(t_data *data)
{
	if (data->envp)
		free_envp(data->envp);
	data->envp = build_envp_tab_from_lst_env(data->env);
}
