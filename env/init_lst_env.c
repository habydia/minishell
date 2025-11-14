/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:00:00 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/14 21:37:09 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../include/minishell.h"
#include "../include/parsing.h"
#include <unistd.h>

void	process_minimum_variables(t_env **envd, char *pwd_variable)
{
	add_or_update_env(envd, pwd_variable);
	free(pwd_variable);
	add_or_update_env(envd, "SHLVL=1");
	add_or_update_env(envd, "_=/usr/bin/env");
}

void	init_minimal_lst_env(t_env **envd)
{
	int		total_path_size;
	char	*cwd;
	char	*pwd_variable;

	pwd_variable = NULL;
	total_path_size = 4096;
	cwd = ft_calloc(total_path_size, sizeof(char));
	if (!cwd)
		return ;
	if (getcwd(cwd, total_path_size) == NULL)
	{
		free(cwd);
		return ;
	}
	pwd_variable = ft_strjoin("PWD=", cwd);
	if (!pwd_variable)
	{
		perror("Malloc faild");
		free(cwd);
		return ;
	}
	free(cwd);
	process_minimum_variables(envd, pwd_variable);
}

void	init_lst_env(t_env **envd, char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	if (!env || !env[0])
	{
		init_minimal_lst_env(envd);
		return ;
	}
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
