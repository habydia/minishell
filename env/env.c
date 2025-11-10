/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:25:08 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/10 03:27:40 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../include/minishell.h"
#include "../include/parsing.h"

void	init_lst_env(t_env **envd, char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (add_back_env(envd) == 1)
			exit(EXIT_FAILURE);
		node = ft_lstlast_env(*envd);
		if (!node)
			free_lst_env(envd, true, 0);
		node->key = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		if (!node->key)
			free_lst_env(envd, true, 0);
		node->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!node->value)
			free_lst_env(envd, true, 0);
		i++;
	}
}

static int	count_env(t_data *data)
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

void	free_envp_at_init(char **envp)
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
				free_all(data, 0, "Error\nMalloc fail in fill_envp_array 1\n");
			data->envp[i] = ft_strjoin(str, tmp->value);
			free(str);
		}
		if (!data->envp[i])
			free_all(data, 0, "Error\nMalloc fail in fill_envp_array 2\n");
		i++;
		tmp = tmp->next;
	}
	data->envp[i] = NULL;
}

void	init_envp(t_data *data)
{
	int	i;

	i = count_env(data);
	if (data->envp)
		free_envp_at_init(data->envp);
	data->envp = ft_calloc((i + 1), sizeof(char *));
	if (!data->envp)
		free_all(data, 0, "Error\nMalloc fail in init_envp 1\n");
	fill_envp_array(data);
}
