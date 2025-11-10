/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:09:37 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/10 04:06:08 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	try_update_existing_env(t_env *env, const char *key, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = value;
			}
			free((char *)key);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

static void	add_new_env_node(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(key);
		if (value)
			free(value);
		return ;
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (!*env)
		*env = new_node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	add_or_update_env(t_env **env, char *str)
{
	char	*key;
	char	*value;
	bool	updated;

	split_key_value(str, &key, &value);
	updated = try_update_existing_env(*env, key, value);
	if (updated == true)
		return ;
	add_new_env_node(env, key, value);
}
