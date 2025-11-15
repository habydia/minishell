/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:46 by willda-s          #+#    #+#             */
/*   Updated: 2025/11/15 02:31:15 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../include/parsing.h"

void	init_data(t_data *data, t_env **envd, char **dst)
{
	t_cmd	*cmds;
	int		saved_exit_status;

	cmds = NULL;
	saved_exit_status = data->exit_status;
	data->dst = dst;
	data->env = *envd;
	data->envp = NULL;
	data->errcode = 0;
	data->exit_status = saved_exit_status;
	data->i = 0;
	data->cmds = cmds;
	data->saved_stdin = -1;
	data->saved_stdout = -1;
}
