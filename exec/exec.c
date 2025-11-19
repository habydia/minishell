/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:13:00 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	execute_pipeline(t_data *data, t_cmd *curr, char *input, int ret)
{
	int		status;
	pid_t	pid;
	t_pipe	p;

	status = 0;
	p.prev_fd = -1;
	while (curr)
	{
		if (curr->next && pipe(p.pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
			handle_child_process(data, curr, &p, input);
		handle_parent_process(&curr, &p);
	}
	ret = waiting(pid, status);
	return (ret);
}

int	exec_cmd(t_data *data, char *input)
{
	int		ret;
	int		single_ret;
	t_cmd	*curr;

	ret = 0;
	curr = data->cmds;
	if (!curr)
		return (data->exit_status);
	update_envp(data);
	if (is_single_cmd(data))
	{
		single_ret = handle_parent_builtins(data, curr, input);
		if (single_ret != -1)
			return (single_ret);
	}
	ret = execute_pipeline(data, curr, input, ret);
	return (ret);
}
