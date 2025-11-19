/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp_exec_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:44:54 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strjoin_checker_envp(char *buffer, char **envp, int i)
{
	if (!buffer)
	{
		while (i >= 0)
		{
			free(envp[i]);
			i--;
		}
		free(envp);
		return (0);
	}
	return (1);
}

void	udpate_envp_from_lst_env_node(t_env *curr, char **envp, int i)
{
	char	*key_equal;

	if (curr->key && curr->value == NULL)
		envp[i] = ft_strdup(curr->key);
	else if (curr->value != NULL)
	{
		free(envp[i]);
		envp[i] = ft_strjoin(curr->key, "=");
	}
	if (!ft_strjoin_checker_envp(envp[i], envp, i))
		return ;
	key_equal = ft_strdup(envp[i]);
	if (curr->value != NULL)
	{
		free(envp[i]);
		envp[i] = ft_strjoin(key_equal, curr->value);
	}
	free(key_equal);
	if (!ft_strjoin_checker_envp(envp[i], envp, i))
		return ;
}
