// Crée fichier temporaire unique                       │
// │     ├─ Lit l'input utilisateur (readline) jusqu'au délimiteur│
// │     ├─ Écrit dans le fichier temporaire                     │
// │     ├─ Ferme le fichier                                     │
// │     └─ Retourne le nom du fichier temporaire

//  Exec lit cmd->redirs                                    │
// │  2. Si type == R_HEREDOC:                                   │
// │     ├─ open(redir->file, O_RDONLY)                          │
// │     ├─ dup2() vers stdin                                    │
// │     └─ unlink() pour supprimer après

#include "../../include/parsing.h"

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

void	handle_heredoc(t_redir *redir)
{
	int		fd;
	char	*line;
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
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(redir->file);
	free(delimiter);
	redir->file = temp_filename;
	// Met à jour le nom du fichier dans la redirection
}
