/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_and_pars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:46 by willda-s          #+#    #+#             */
/*   Updated: 2025/10/25 03:23:20 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../include/parsing.h"



void	init_data(t_data *data, t_env **envd, char **dst)
{
	t_cmd	*cmds;

	cmds = NULL;
	data->dst = dst;
	data->env = *envd;
	data->envp = NULL;
	data->errcode = 0;
	data->i = 0;

	data->cmds = cmds;
}
