/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_and_pars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:46 by willda-s          #+#    #+#             */
/*   Updated: 2025/06/30 14:22:35 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static int	init_lst_pars(t_pars **pars, char **dst)
// {
// 	t_pars	*node;
// 	int		i;

// 	i = 0;
// 	while (dst && dst[i])
// 	{
// 		if (add_back_pars(pars) == 1)
// 			return (1);
// 		node = ft_lstlast_pars(*pars);
// 		if (!node)
// 			return (1);
// 		node->word = ft_strdup(dst[i]);
// 		if (!node->word)
// 			return (1);
// 		node->type = NUL;
// 		i++;
// 	}
// 	return (0);
// }

void	init_data(t_data *data, t_env **envd, char **dst)
{
	// t_cmd	*cmd;
	// t_pars	*pars;
	// pars = NULL;
	// cmd = NULL;
	data->dst = dst;
	data->env = *envd;
	data->envp = NULL;
	data->errcode = 0;
	data->i = 0;
	// if (init_lst_pars(&pars, data->dst) == 1)
	// free_lst_pars(&pars);
	// free_tab(dst);
	// free_lst_env(envd, true, 0);
	// data->pars = pars;
	// data->cmd = cmd;
}
