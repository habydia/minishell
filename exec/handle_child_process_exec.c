/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child_process_exec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:41:30 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/08 15:50:44 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "env.h"
// #include "exec.h"
// #include "parsing.h"

// static void	setup_pipes(t_cmd *curr, int prev_fd, int *pipe_fd)
// {
// 	if (prev_fd != -1)
// 	{
// 		dup2(prev_fd, STDIN_FILENO);
// 		close(prev_fd);
// 	}
// 	if (curr->next)
// 	{
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_fd[1]);
// 	}
// }

// static void	handle_redirections_or_exit(t_data *data, t_cmd *curr)
// {
// 	if (apply_redirections(curr) == -1)
// 	{
// 		free_all(data, 1, NULL);
// 		exit(1);
// 	}
// }

// static int	try_execute_builtin(t_data *data, t_cmd *curr, char *input)
// {
// 	int	ret;

// 	ret = 0;
// 	if (is_builtins(curr->name))
// 	{
// 		ret = exec_builtins(curr, data, data->envp, input);
// 		free_all(data, ret, NULL);
// 	}
// 	return (ret);
// }

// static void	execute_external_cmd(t_data *data, t_cmd *curr, int ret)
// {
// 	curr->path = get_path(data->envp, curr->args[0], &ret);
// 	if (!curr->path)
// 	{
// 		write(2, "Command not found: ", 19);
// 		write(2, curr->args[0], strlen(curr->args[0]));
// 		write(2, "\n", 1);
// 		free_all(data, 127, NULL);
// 		exit(127);
// 	}
// 	close(data->saved_stdin);
// 	close(data->saved_stdout);
// 	execve(curr->path, curr->args, data->envp);
// 	perror("execve");
// 	free_all(data, 1, NULL);
// 	exit(1);
// }

// int	handle_child_process(t_data *data, t_cmd *curr,
// 							int prev_fd, int *pipe_fd, char *input)
// {
// 	int	ret;

// 	ret = 0;
// 	setup_pipes(curr, prev_fd, pipe_fd);
// 	handle_redirections_or_exit(data, curr);
// 	ret = try_execute_builtin(data, curr, input);
// 	execute_external_cmd(data, curr, ret);
// }

