/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 05:00:34 by hadia             #+#    #+#             */
/*   Updated: 2025/11/11 03:37:49 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell_signals.h"
#include <sys/ioctl.h>

volatile sig_atomic_t g_heredoc_interrupted = 0;

void handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void setup_sigint_heredoc(void)
{
	struct sigaction	sa_int;

	g_heredoc_interrupted = 0;
	sa_int.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
}

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

static int	write_in_heredoc_file(int fd, const char *delimiter)
{
	char	*line;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	setup_sigint_heredoc();
	while (1)
	{
		line = readline("> ");
		if (g_heredoc_interrupted)
		{
			free(line);
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
			handle_signals();
			return (-1);
		}
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd((char *)delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(stdin_backup);
	handle_signals();
	return (0);
}

void	handle_heredoc(t_redir *redir)
{
	int		fd;
	char	*temp_filename;
	char	*delimiter;

	if (!redir || !redir->file)
		return ;
	delimiter = ft_strdup(redir->file);
	temp_filename = generate_temp_filename();
	if (!temp_filename || !delimiter)
	{
		free(delimiter);
		return ;
	}
	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		free(temp_filename);
		free(delimiter);
		return ;
	}
	if(write_in_heredoc_file(fd, delimiter) < 0)
	{
		 close(fd);
   		 unlink(temp_filename);  // Supprimer le fichier !
   		 free(temp_filename);
   		 free(delimiter);
   		 redir->file = NULL;
		 g_exit_status = 130;
   		 return ;
	}
	close(fd);
	free(redir->file);
	free(delimiter);
	redir->file = temp_filename;
}
