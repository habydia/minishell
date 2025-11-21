/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:35:44 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/21 18:16:18 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	handle_signal(int signal_num)
{
	if (signal_num == SIGSEGV)
		write(2, "Segmentation fault\n", 19);
	else if (signal_num == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	else if (signal_num == SIGINT)
		ft_putchar_fd('\n', 2);
}

int	waiting(pid_t pid, int status)
{
	int		ret;
	pid_t	pid_at_exit;
	int		signal_num;

	ret = 0;
	while (1)
	{
		pid_at_exit = wait(&status);
		if (pid_at_exit == pid)
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				signal_num = WTERMSIG(status);
				ret = 128 + signal_num;
				handle_signal(signal_num);
			}
		}
		if (pid_at_exit < 0)
			break ;
	}
	return (ret);
}
