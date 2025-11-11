/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child_process_exec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:41:30 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/11 07:45:21 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "parsing.h"

int	child_pipe_redir_dup2_close_secure(t_cmd *curr, t_pipe *p)
{
	if (p->prev_fd != -1)
	{
		if (dup2(p->prev_fd, STDIN_FILENO) == -1)
		{
			close(p->prev_fd);
			return (-1);
		}
		close(p->prev_fd);
	}
	if (curr->next)
	{
		close(p->pipe_fd[0]);
		if (dup2(p->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close(p->pipe_fd[1]);
			return (-1);
		}
		close(p->pipe_fd[1]);
	}
	return (0);
}

void	check_file_points(t_data *data, t_cmd *curr, int *ret)
{
	if (strcmp(curr->args[0], ".") == 0)
	{
		write(2,
			".: filename argument required\n.: usage: . filename [arguments]\n",
			64);
		*ret = 2;
		free_all(data, *ret, NULL);
	}
	if (strcmp(curr->args[0], "..") == 0)
	{
		write(2, "Minishell: ..: command not found\n", 33);
		*ret = 127;
		free_all(data, *ret, NULL);
	}
}

void	check_command_path(t_cmd *curr, t_data *data, int *ret)
{
	if (!curr->args[0] || curr->args[0][0] == '\0')
	{
		*ret = 0;
		free_all(data, *ret, NULL);
	}
	check_file_points(data, curr, ret);
	curr->path = handle_access_cmd(curr->args[0], ret);
	if (!curr->path && *ret == 0)
		curr->path = get_path(data->envp, curr->args[0], ret);
	if (!curr->path)
	{
		if (*ret != 126)
		{
			write(2, "Minishell: command not found: ", 30);
			write(2, curr->args[0], strlen(curr->args[0]));
			write(2, "\n", 1);
			*ret = 127;
		}
		free_all(data, *ret, NULL);
	}
}

void	handle_child_process(t_data *data, t_cmd *curr, t_pipe *p, char *input)
{
	int	ret;

	ret = 0;
	if (child_pipe_redir_dup2_close_secure(curr, p) == -1)
	{
		perror("dup2");
		free_all(data, 1, NULL);
	}
	if (apply_redirections_input_output(curr) == -1)
		free_all(data, 1, NULL);
	if (!curr->name)
		free_all(data, 0, NULL);
	if (is_builtins(curr->name))
	{
		ret = exec_builtins(curr, data, data->envp, input);
		free_all(data, ret, NULL);
	}
	check_command_path(curr, data, &ret);
	if (!curr->path)
		free_all(data, ret, NULL);
	close(data->saved_stdin);
	close(data->saved_stdout);
	execve(curr->path, curr->args, data->envp);
	perror("execve");
	free_all(data, 1, NULL);
}
