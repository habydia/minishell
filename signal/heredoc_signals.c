/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:28:13 by hadia             #+#    #+#             */
/*   Updated: 2025/11/14 19:30:05 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_sigint_heredoc(void)
{
	struct sigaction	sa_int;

	g_heredoc_interrupted = 0;
	sa_int.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
}

void	apply_ctrld(char const *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by eof (wanted `",
		2);
	ft_putstr_fd((char *)delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

void	apply_handle_signals(char *line, int stdin_backup)
{
	free(line);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	handle_signals();
}

void	handle_heredoc_error(t_redir *redir, char *temp_filename,
		char *delimiter, int fd)
{
	close(fd);
	unlink(temp_filename);
	free(temp_filename);
	free(delimiter);
	redir->file = NULL;
	g_exit_status = 130;
}
