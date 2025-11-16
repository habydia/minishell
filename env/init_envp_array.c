/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:25:08 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/16 16:24:04 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_lst_env_node(t_data *data)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = data->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	free_envp_array_at_init(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	fill_envp_array(t_data *data)
{
	t_env	*tmp;
	char	*str;
	int		i;

	tmp = data->env;
	i = 0;
	while (tmp)
	{
		if (tmp->value == NULL)
			data->envp[i] = ft_strdup(tmp->key);
		else
		{
			str = ft_strjoin(tmp->key, "=");
			if (!str)
				free_all(data, 0, "Error\nMalloc fail in fill_envp_tab \n");
			data->envp[i] = ft_strjoin(str, tmp->value);
			free(str);
		}
		if (!data->envp[i])
			free_all(data, 0, "Error\nMalloc fail in fill_envp_tab \n");
		i++;
		tmp = tmp->next;
	}
	data->envp[i] = NULL;
}

void	init_envp_array(t_data *data)
{
	int	i;

	i = count_lst_env_node(data);
	if (data->envp)
		free_envp_array_at_init(data->envp);
	data->envp = ft_calloc((i + 1), sizeof(char *));
	if (!data->envp)
		free_all(data, 0, "Error\nMalloc fail in init_envp \n");
	fill_envp_array(data);
}
