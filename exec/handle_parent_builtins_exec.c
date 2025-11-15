/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parent_builtins_exec.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:26:37 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/15 04:36:36 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "parsing.h"

void	reset_std_in_out(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	save_std_in_out(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
	{
		perror("dup");
		return (-1);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		perror("dup");
		close(*saved_stdin);
		return (-1);
	}
	return (0);
}

int	handle_exit_builtin(t_data *data, t_cmd *curr, char *input)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	if (save_std_in_out(&saved_stdin, &saved_stdout) == -1)
		return (1);
	if (apply_redirections_input_output(curr) == -1)
	{
		reset_std_in_out(saved_stdin, saved_stdout);
		free_all(data, 1, NULL);
	}
	ret = exec_builtins(curr, data, data->envp, input);
	reset_std_in_out(saved_stdin, saved_stdout);
	free_all(data, ret, NULL);
}

int	handle_parent_builtins(t_data *data, t_cmd *curr, char *input)
{
	int	ret;
	int	saved_stdin;
	int	saved_stdout;

	ret = 0;
	if (!curr->name)
		return (-1);
	if (!ft_strcmp(curr->name, "exit"))
		handle_exit_builtin(data, curr, input);
	if (!ft_strcmp(curr->name, "cd") || !ft_strcmp(curr->name, "export")
		|| !ft_strcmp(curr->name, "unset"))
	{
		if (save_std_in_out(&saved_stdin, &saved_stdout) == -1)
			return (1);
		if (apply_redirections_input_output(curr) == -1)
		{
			reset_std_in_out(saved_stdin, saved_stdout);
			return (1);
		}
		ret = exec_builtins(curr, data, data->envp, input);
		reset_std_in_out(saved_stdin, saved_stdout);
		return (ret);
	}
	return (-1);
}
