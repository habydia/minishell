/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:32:47 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/31 16:15:08 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_tab(char **dst)
{
	int	i;

	i = 0;
	while (dst && dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

int	exec_builtins(t_data *data, char **env, char *input)
{
	t_cmd	*cmd;
	int		status;

	cmd = data->cmds;
	status = 0;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strncmp(cmd->args[0], "env", 3) == 0 && ft_strlen(cmd->args[0]) == 3)
		status = ft_env(env);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0
		&& ft_strlen(cmd->args[0]) == 3)
		status = ft_pwd();
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0
		&& ft_strlen(cmd->args[0]) == 4)
	{
		status = ft_exit(cmd->args, data);
		if (status != -12)
			// remplacer-12 par une valeur spéciale si tu veux signaler "ne pas quitter"
		{
			free(input);
			ft_free_tab(cmd->args);
			free_all(data, status, NULL);
			exit(status);
		}
	}
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0
		&& ft_strlen(cmd->args[0]) == 4)
		status = ft_echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0
		&& ft_strlen(cmd->args[0]) == 2)
		status = ft_cd(cmd->args);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
		&& ft_strlen(cmd->args[0]) == 6)
		status = ft_export(cmd->args, env);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& ft_strlen(cmd->args[0]) == 5)
		status = ft_unset(cmd->args, env);
	else
	{
		printf("minishell: %s: command not found\n", input);
		status = 127; // oui, c’est la bonne valeur pour "command not found"
	}
	return (status);
}

/*Parcourir ta liste chaine pour trouver les builtins*/ // DONE