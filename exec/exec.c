#include "parsing.h"

// lose(), read(), write(), dup2(), pipe()

///////////////////////////////
///////GET PATH - UTILS////////

void	ft_free_tab_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*envp_search(char **envp)
{
	if (!envp || !*envp)
		return (NULL);
	while (*envp)
	{
		// printf("*envp=%s\n", *envp);
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

int	path_check(char *path, int *ret)
{
	if (path == NULL)
	{
		*ret = 127;
		return (1);
	}
	return (0);
}

char	*strjoin_check_error(char *str)
{
	if (!str)
		return (NULL);
	return (str);
}
/////////////////////////////////////////////
///////////////GET-PATH//////////////////////
//////////////////////////////////////////////
char	*get_path_in_paths_list(char **paths, int *ret, char *buffer,
		char *argv_cmd)
{
	char	*new_path;
	int		i;

	i = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		buffer = ft_strjoin(paths[i], "/");
		strjoin_check_error(buffer);
		new_path = ft_strjoin(buffer, argv_cmd);
		free(buffer);
		strjoin_check_error(new_path);
		if (new_path != NULL && access(new_path, F_OK | X_OK) == 0)
		{
			ft_free_tab_str(paths);
			return (new_path);
		}
		free(new_path);
		i++;
	}
	ft_free_tab_str(paths);
	*ret = 127;
	return (NULL);
}

char	*get_path(char **envp, char *argv_cmd, int *ret)
{
	char	*path;
	char	**paths;
	char	*buffer;

	buffer = NULL;
	// printf("OKKKKKKKKKKKKKKKKKKKKKKK");
	if (!argv_cmd)
	{
		*ret = 1;
		return (NULL);
	}
	else
	{
		if (access(argv_cmd, F_OK | X_OK) == 0)
			return (argv_cmd);
	}
	path = envp_search(envp);
	printf("PATHDEBUG %s\n", envp[0]);
	if (path_check(path, ret) == 1)
		return (NULL);
	paths = ft_split(path, ':');
	printf("HERE2\n");
	return (get_path_in_paths_list(paths, ret, buffer, argv_cmd));
}
//////////////////////////////////////////////
/// UTILS POUR L'EXEC/// pas encore utilier !
/////////////////////////////////////////////

//////////////////////////////////////////////
// Générer un nom unique pour chaque heredoc
//////////////////////////////////////////////
char	*get_unique_heredoc_path(void)
{
	int		i;
	char	*path;
	int		fd;
	char	*index;

	i = 0;
	while (1)
	{
		index = ft_itoa(i);
		path = ft_strjoin("/tmp/heredoc", index);
		free(index);
		fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0644);
		if (fd != -1)
		{
			close(fd);
			return (path);
		}
		free(path);
		i++;
	}
}

//////////////////////////////////////////////
// Gérer un heredoc et retourner son fichier
//////////////////////////////////////////////
char	*handle_heredoc(char *delimiter)
{
	char	*line;
	char	*heredoc_path;
	int		fd;

	heredoc_path = get_unique_heredoc_path();
	if (!heredoc_path)
		return (NULL);
	fd = open(heredoc_path, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		perror("open heredoc");
		free(heredoc_path);
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (heredoc_path);
}

//////////////////////////////////////////////
// Appliquer les redirections (in/out)
//////////////////////////////////////////////
void	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;
	char	*file;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == R_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd != -1)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		else if (redir->type == R_OUT_TRUNC)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd != -1)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		else if (redir->type == R_OUT_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd != -1)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		else if (redir->type == R_HEREDOC) // && redir->delimiter)
		{
			file = handle_heredoc(redir->file);
			if (file)
			{
				fd = open(file, O_RDONLY);
				if (fd != -1)
				{
					dup2(fd, STDIN_FILENO);
					close(fd);
				}
				unlink(file);
				free(file);
			}
		}
		redir = redir->next;
	}
}

//////////////////////////////////////////////
// Construire argv à partir des noeuds pars
//////////////////////////////////////////////
// char	**build_argv(t_pars *pars)
// {
// 	int		count;
// 	int		i;
// 	t_pars	*tmp;
// 	char	**argv;

// 	count = 0;
// 	i = 0;
// 	tmp = pars;
// 	while (tmp)
// 	{
// 		if ((tmp->type & COMMANDS) || (tmp->type & ARGS))
// 			count++;
// 		tmp = tmp->next;
// 	}
// 	argv = malloc(sizeof(char *) * (count + 1));
// 	if (!argv)
// 		return (NULL);
// 	tmp = pars;
// 	while (tmp)
// 	{
// 		if ((tmp->type & COMMANDS) || (tmp->type & ARGS))
// 			argv[i++] = ft_strdup(tmp->word);
// 		tmp = tmp->next;
// 	}
// 	argv[i] = NULL;
// 	return (argv);
// }

//////////////////////////////////////////////
// Libérer argv
//////////////////////////////////////////////
void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return ;
}

//////////////////////////////////////////////
// Construire envp depuis liste chaînée env
//////////////////////////////////////////////
// char	**build_envp_from_lst_env(t_env *env)
// {
// 	int		count;
// 	t_env	*tmp;
// 	char	**envp;

// 	count = 0, i;
// 	count = 0, i = 0;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		count++;
// 		tmp = tmp->next;
// 	}
// 	envp = malloc(sizeof(char *) * (count + 1));
// 	if (!envp)
// 		return (NULL);
// 	tmp = env;
// 	while (tmp)
// 		envp[i++] = ft_strdup(tmp->value), tmp = tmp->next;
// 	envp[i] = NULL;
// 	return (envp);
// }

// //////////////////////////////////////////////
// // Libérer envp
// //////////////////////////////////////////////
// void	free_envp(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	if (!envp)
// 		return ;
// 	while (envp[i])
// 	{
// 		free(envp[i]);
// 		i++;
// 	}
// 	free(envp);
// }

// //////////////////////////////////////////////
// // Mettre à jour envp dans data
// //////////////////////////////////////////////
// void	update_envp(t_data *data)
// {
// 	if (data->envp)
// 		free_envp(data->envp);
// 	data->envp = build_envp_from_lst_env(data->env);
// }

//////////////////////////////////////////////
// Exécuter la liste de commandes avec pipes
//////////////////////////////////////////////
int	exec_cmd(t_cmd *cmds, t_data *data)
{
	pid_t	pid;

	// int		ret;
	t_cmd *curr; // t_exec	*curr;
	curr = cmds;
	printf(" %s", curr->args[0]);
	int pipe_fd[2], prev_fd = -1;
	// ret = 0;
	// update_envp(data); ne marche pas pour l'instant
	while (curr)
	{
		if (curr->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (curr->next)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			apply_redirections(curr);
			printf("%s", curr->args[0]);
			curr->path = getenv("PATH"); // get_path(data->envp, curr->args[0],
											// &ret);
			printf("OKKKKKKKKKKKKKKKKKKKKKKKKKKK\n");
			printf("HERE\n");
			printf("PATH:%s\n", curr->path);
			// get_path a mettre a ce niveau pour chope la commande si il n'y a pas absolute path.
			// il faut incorporer le fait que si c'est un builtins,
			// il faut qu'il s'execute dans cette fonction cmd
			execve(curr->path, curr->args, data->envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (curr->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		curr = curr->next;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
