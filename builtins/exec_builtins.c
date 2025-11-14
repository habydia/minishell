/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:32:47 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/13 17:55:41 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit_handle(t_cmd *cmd, t_data *data, int status, char *input)
{
	status = ft_exit(cmd->args, data);
	if (status != 2)
	{
		free(input);
		free_all(data, status, NULL);
		exit(status);
	}
	return (status);
}

int	exec_builtins(t_cmd *cmd, t_data *data, char **env, char *input)
{
	int	status;

	status = 0;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		status = ft_env(env);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		status = ft_exit_handle(cmd, data, status, input);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		status = ft_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		status = ft_cd(cmd->args);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		status = ft_export(cmd->args, env, data);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		status = ft_unset(cmd->args, env, data);
	else
	{
		printf("minishell: %s: command not found\n", input);
		status = 127;
	}
	return (status);
}
