/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parent_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:39:40 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/20 11:19:38 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(t_cmd **curr, t_pipe *p)
{
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if ((*curr)->next)
	{
		close(p->pipe_fd[1]);
		p->prev_fd = p->pipe_fd[0];
	}
	*curr = (*curr)->next;
}
