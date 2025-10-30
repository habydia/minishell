/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:13:00 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/30 14:03:14 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
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

// char	*envp_search(char **envp)
// {
// 	if (!envp || !*envp)
// 		return (NULL);
// 	while (*envp)
// 	{
// 		// printf("*envp=%s\n", *envp);
// 		if (ft_strncmp("PATH=", *envp, 5) == 0)
// 			return (*envp + 5);
// 		envp++;
// 	}
// 	return (NULL);
// }

// int	path_check(char *path, int *ret)
// {
// 	if (path == NULL)
// 	{
// 		*ret = 127;
// 		return (1);
// 	}
// 	return (0);
// }

/////////////////////////////////////////////
///////////////GET-PATH//////////////////////
//////////////////////////////////////////////
// char	*get_path_in_paths_list(char **paths, int *ret, char *buffer,
// 		char *argv_cmd)
// {
// 	char	*new_path;
// 	int		i;

// 	i = 0;
// 	if (paths == NULL)
// 		return (NULL);
// 	while (paths[i])
// 	{
// 		buffer = ft_strjoin(paths[i], "/");
// 		if (!buffer)
// 		{
// 			ft_free_tab_str(paths);
// 			*ret = 1;
// 			return (NULL);
// 		}
// 		new_path = ft_strjoin(buffer, argv_cmd);
// 		free(buffer);
// 		if (!new_path)
// 		{
// 			ft_free_tab_str(paths);
// 			*ret = 1;
// 			return (NULL);
// 		}
// 		if (access(new_path, F_OK | X_OK) == 0)
// 		{
// 			ft_free_tab_str(paths);
// 			return (new_path);
// 		}
// 		free(new_path);
// 		i++;
// 	}
// 	ft_free_tab_str(paths);
// 	*ret = 127;
// 	return (NULL);
// }

//////////////////////////////////////////////
/// GET PATH pour choper le path de chaque commandes, test l'excution
////////////////////////////////////////////

// char	*get_path(char **envp, char *argv_cmd, int *ret)
// {
// 	char	*path;
// 	char	**paths;
// 	char	*buffer;

// 	buffer = NULL;
// 	// printf("OKKKKKKKKKKKKKKKKKKKKKKK");
// 	if (!argv_cmd)
// 	{
// 		*ret = 1;
// 		return (NULL);
// 	}
// 	if (access(argv_cmd, F_OK | X_OK) == 0)
// 		return (ft_strdup(argv_cmd));
// 	path = envp_search(envp);
// 	if (path_check(path, ret) == 1)
// 		return (NULL);
// 	paths = ft_split(path, ':');
// 	if (!paths)
// 	{
// 		*ret = 1;
// 		return (NULL);
// 	}
// 	return (get_path_in_paths_list(paths, ret, buffer, argv_cmd));
// }
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
		// verifier que itoa ne casse pas
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
// char	*handle_heredoc(char *delimiter)
// {
// 	char	*line;
// 	char	*heredoc_path;
// 	int		fd;

// 	heredoc_path = get_unique_heredoc_path();
// 	if (!heredoc_path)
// 		return (NULL);
// 	fd = open(heredoc_path, O_WRONLY | O_TRUNC);
// 	if (fd == -1)
// 	{
// 		perror("open heredoc");
// 		free(heredoc_path);
// 		return (NULL);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	close(fd);
// 	return (heredoc_path);
// }

//////////////////////////////////////////////
// Appliquer les redirections (in/out)
//////////////////////////////////////////////
// void	apply_redirections(t_cmd *cmd)
// // gerer les cas ou les opens cassent et les dup2
// {
// 	t_redir *redir;
// 	int fd;
// 	char *file = NULL;

// 	redir = cmd->redirs;
// 	while (redir)
// 	{
// 		if (redir->type == R_IN)
// 		{
// 			fd = open(redir->file, O_RDONLY);
// 			if (fd != -1)
// 			{
// 				dup2(fd, STDIN_FILENO);
// 				close(fd);
// 			}
// 		}
// 		else if (redir->type == R_OUT_TRUNC)
// 		{
// 			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd != -1)
// 			{
// 				dup2(fd, STDOUT_FILENO);
// 				close(fd);
// 			}
// 		}
// 		else if (redir->type == R_OUT_APPEND)
// 		{
// 			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd != -1)
// 			{
// 				dup2(fd, STDOUT_FILENO);
// 				close(fd);
// 			}
// 		}
// 		else if (redir->type == R_HEREDOC)
// 		{
// 			if (redir->file)
// 			{
// 				fd = open(redir->file, O_RDONLY);
// 				if (fd != -1)
// 				{
// 					dup2(fd, STDIN_FILENO);
// 					close(fd);
// 				}
// 				unlink(file);
// 				free(file);
// 			}
// 		}
// 		redir = redir->next;
// 	}
// }

/*
parsing :
- trouver hd
- open 2 fd ( 1 ecriture (parsing) | 1 lecture (exec))
- unlink immediatement le fichier (plus reference sur le filesystem)
- rempli le fd d'ecriture avec le contenu du hd puis close le fd d'ecriture
- envoie le fd de lecture a l'exec,
	qui l'utilisera puis closera une fois les operations effectuees

*/

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

// //////////////////////////////////////////////
// // Libérer envp
// //////////////////////////////////////////////
void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

//////////////////////////////////////////////
// Exécuter la liste de commandes avec pipes
//////////////////////////////////////////////
int	exec_cmd(t_data *data)
{
	pid_t	pid;
	int		ret;

	t_cmd *curr;
	curr = data->cmds;
	
	int pipe_fd[2]; 
	int prev_fd;
	prev_fd = -1;
	ret = 0;
	update_envp(data);
	while (curr)
	{
		if (curr->next && pipe(pipe_fd) == -1)// securisation du pipe dans le process parent
		{
			perror("pipe");
			return (1);
		}
		pid = fork();// fork pour la creations des enfants.
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
			if(apply_redirections(curr) == -1) // apply redirections securise
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				free_all(data, ret, "");
				exit(EXIT_FAILURE);
			}
			curr->path = get_path(data->envp, curr->args[0], &ret); // chope le path de la commande
			if (!curr->path)
			{
				fprintf(stderr, "Command not found: %s\n", curr->args[0]);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				free_all(data, ret, "");// mettre la bonne str de retour
				exit(EXIT_FAILURE);
			}
			execve(curr->path, curr->args, data->envp);
			perror("execve");
			free_all(data, 0, "MERDE");
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
