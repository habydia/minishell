/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:46 by willda-s          #+#    #+#             */
/*   Updated: 2025/11/16 16:24:06 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, t_env **envd)
{
	t_cmd	*cmds;
	int		saved_exit_status;

	cmds = NULL;
	saved_exit_status = data->exit_status;
	data->env = *envd;
	data->envp = NULL;
	data->exit_status = saved_exit_status;
	data->cmds = cmds;
}
