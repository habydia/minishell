/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parent_builtins_exec.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:26:37 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/10 02:59:38 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "parsing.h"

int	handle_parent_builtins(t_data *data, t_cmd *curr, char *input)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(curr->name, "exit"))
	{
		if (apply_redirections_input_output(curr) == -1)
		{
			free_all(data, 1, NULL);
			exit(1);
		}
		ret = exec_builtins(curr, data, data->envp, input);
		free_all(data, ret, NULL);
	}
	if (!ft_strcmp(curr->name, "cd") || !ft_strcmp(curr->name, "export")
		|| !ft_strcmp(curr->name, "unset"))
	{
		if (apply_redirections_input_output(curr) == -1)
			return (1);
		ret = exec_builtins(curr, data, data->envp, input);
		return (ret);
	}
	return (-1);
}
