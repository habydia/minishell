/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:35:44 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/14 23:06:30 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "parsing.h"

int	is_single_cmd(t_data *data)
{
	if (!data || !data->cmds)
		return (0);
	return (data->cmds->next == NULL);
}

int	is_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	save_std_in_out(t_data *data)
{
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	if (data->saved_stdin == -1 || data->saved_stdout == -1)
	{
		perror("dup");
		exit(1);
	}
}

void	reset_std_in_out(t_data *data)
{
	if (dup2(data->saved_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		exit(1);
	}
	if (dup2(data->saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout");
		exit(1);
	}
	close(data->saved_stdin);
	close(data->saved_stdout);
}

int	waiting(pid_t pid, int status)
{
	int		ret;
	pid_t	pid_at_exit;

	ret = 0;
	while (1)
	{
		pid_at_exit = wait(&status);
		if (pid_at_exit == pid)
			ret = WEXITSTATUS(status);
		if (pid_at_exit < 0)
			break ;
	}
	return (ret);
}
