/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections_exec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:00:08 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 00:08:55 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in_open_and_dup_close_secure(t_redir *redir, bool flag)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	if (flag)
		unlink(redir->file);
	return (1);
}

int	redir_out_open_and_dup_close_secure(t_redir *redir, t_redir_type type)
{
	int	fd;

	fd = -1;
	if (type == R_OUT_TRUNC)
		fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == R_OUT_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

int	apply_redirections_input_output(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == R_IN)
			if (redir_in_open_and_dup_close_secure(redir, false) == -1)
				return (-1);
		if (redir->type == R_HEREDOC)
			if (redir_in_open_and_dup_close_secure(redir, true) == -1)
				return (-1);
		if (redir->type == R_OUT_TRUNC)
			if (redir_out_open_and_dup_close_secure(redir, R_OUT_TRUNC) == -1)
				return (-1);
		if (redir->type == R_OUT_APPEND)
			if (redir_out_open_and_dup_close_secure(redir, R_OUT_APPEND) == -1)
				return (-1);
		redir = redir->next;
	}
	return (0);
}
