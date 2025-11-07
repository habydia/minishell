/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:52:57 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/07 02:08:39 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_free.h"
#include "parsing.h"
#include "exec.h"

void	free_tab(char **dst)
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

int	free_all(t_data *data, int errcode, char *str)
{
	if(data->saved_stdin || data->saved_stdout)
		reset_std_in_out(data);
	if (data->env)
		free_lst_env(&data->env, false, 0);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->envp)
		free_envp(data->envp);
	if (data->dst)
		free_tab(data->dst);
	if (str)
		ft_putstr_fd(str, 2);
	exit(errcode);
}
