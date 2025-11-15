/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:52:57 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/15 04:25:29 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "ft_free.h"
#include "parsing.h"

int	free_all(t_data *data, int errcode, char *str)
{
	if (data->env)
		free_lst_env(&data->env, false, 0);
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->envp)
		free_envp(data->envp);
	if (str)
		ft_putstr_fd(str, 2);
	exit(errcode);
}
