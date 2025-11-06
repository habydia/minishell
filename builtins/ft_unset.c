/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:57:49 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/06 22:43:47 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	identifier_correct(char *str)
{
	int		i;
	char	*eq_pos;
	int		len;

	eq_pos = ft_strchr(str, '=');
	i = 1;
	if (eq_pos)
		len = eq_pos - str;
	else
		len = ft_strlen(str);
	if (len == 0)
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	while (i < len)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	delete_env_node(t_env **env_list, const char *key_to_del)
{
	t_env	*prev;
	t_env	*curr;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key_to_del) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	delete_envp_entry(char **envp, const char *key_to_del)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(envp[j], key_to_del, ft_strlen(key_to_del)) == 0
			&& (envp[j][ft_strlen(key_to_del)] == '='
			|| envp[j][ft_strlen(key_to_del)] == '\0'))
		{
			free(envp[j]);
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			return ;
		}
		j++;
	}
}

int	ft_unset(char **args, char **env, t_data *data)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	i = 1;
	if (!args[1])
		return (exit_code);
	while (args[i])
	{
		if (!identifier_correct(args[i]))
		{
			write(2, "unset: `", 8);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 27);
			exit_code = 1;
		}
		else
		{
			delete_env_node(&data->env, args[i]);
			delete_envp_entry(env, args[i]);
		}
		i++;
	}
	return (exit_code);
}
