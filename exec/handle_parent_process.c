/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parent_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:39:40 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 15:45:31 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(t_cmd **curr, t_pipe *p)
{
	ignore_sigint_in_parent();
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if ((*curr)->next)
	{
		close(p->pipe_fd[1]);
		p->prev_fd = p->pipe_fd[0];
	}
	*curr = (*curr)->next;
}
