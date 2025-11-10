/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parent_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:39:40 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/10 03:00:28 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "parsing.h"

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
