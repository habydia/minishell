/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 05:00:34 by hadia             #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_temp_filename(void)
{
	static int	heredoc_count = 0;
	char		*count_str;
	char		*filename;
	char		*temp;

	count_str = ft_itoa(heredoc_count++);
	temp = ft_strjoin("/tmp/.heredoc_", count_str);
	filename = ft_strjoin(temp, "_minishell");
	free(count_str);
	free(temp);
	return (filename);
}

static int	handle_interruptions(char *line, char *delimiter, int stdin_backup)
{
	if (g_signal_status == SIG_HEREDOC_INTERRUPTED)
	{
		apply_handle_signals(line, stdin_backup);
		return (-1);
	}
	if (!line)
	{
		apply_ctrld(delimiter);
		return (1);
	}
	if (strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	write_in_heredoc_file(int fd, const char *delimiter)
{
	char	*line;
	int		stdin_backup;
	int		status;

	stdin_backup = dup(STDIN_FILENO);
	setup_sigint_heredoc();
	while (1)
	{
		line = readline("> ");
		status = handle_interruptions(line, (char *)delimiter, stdin_backup);
		if (status == -1)
			return (-1);
		if (status == 1)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(stdin_backup);
	handle_signals();
	return (0);
}

static int	init_heredoc(t_redir *redir, char **temp_filename, char **delimiter,
		int *fd)
{
	*delimiter = ft_strdup(redir->file);
	*temp_filename = generate_temp_filename();
	if (!*temp_filename || !*delimiter)
	{
		free(*delimiter);
		return (-1);
	}
	*fd = open(*temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd < 0)
	{
		free(*temp_filename);
		free(*delimiter);
		return (-1);
	}
	return (0);
}

void	handle_heredoc(t_redir *redir)
{
	int		fd;
	char	*temp_filename;
	char	*delimiter;

	if (!redir || !redir->file)
		return ;
	if (init_heredoc(redir, &temp_filename, &delimiter, &fd) < 0)
		return ;
	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		free(temp_filename);
		free(delimiter);
		return ;
	}
	if (write_in_heredoc_file(fd, delimiter) < 0)
	{
		handle_heredoc_error(redir, temp_filename, delimiter, fd);
		return ;
	}
	close(fd);
	free(redir->file);
	free(delimiter);
	redir->file = temp_filename;
}
