/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:57:49 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/16 16:26:03 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_variable_key_is_correct(char *str)
{
	int		i;
	int		len;
	char	*equal_position;

	i = 1;
	equal_position = ft_strchr(str, '=');
	if (equal_position)
		len = equal_position - str;
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

void	delete_env_node_variable(t_env **env_list, const char *key_to_del)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env_list;
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
			curr = NULL;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	delete_envp_tab_variable(char **envp, const char *key_to_del)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key_to_del, ft_strlen(key_to_del)) == 0
			&& (envp[i][ft_strlen(key_to_del)] == '='
			|| envp[i][ft_strlen(key_to_del)] == '\0'))
		{
			free(envp[i]);
			j = i;
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL;
			return ;
		}
		i++;
	}
}

int	ft_unset(char **args, char **envp, t_data *data)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!args[1])
		return (ret);
	while (args[i])
	{
		if (!check_if_variable_key_is_correct(args[i]))
		{
			write(2, "unset: `", 8);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 27);
			ret = 1;
		}
		else
		{
			delete_env_node_variable(&data->env, args[i]);
			delete_envp_tab_variable(envp, args[i]);
		}
		i++;
	}
	return (ret);
}
