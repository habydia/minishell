/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:32:47 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_handle(t_cmd *cmd, t_data *data, int ret, char *input)
{
	(void)data;
	(void)input;
	ret = ft_exit(cmd->args);
	return (ret);
}

int	exec_builtins(t_cmd *cmd, t_data *data, char **env, char *input)
{
	int	ret;

	ret = 0;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		ret = ft_env(env);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ret = ft_exit_handle(cmd, data, ret, input);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		ret = ft_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ret = ft_cd(cmd->args);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ret = ft_export(cmd->args, env, data);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ret = ft_unset(cmd->args, env, data);
	else
	{
		printf("Minishell: %s: command not found\n", input);
		ret = 127;
	}
	return (ret);
}
