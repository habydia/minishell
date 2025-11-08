/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:13:00 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/08 17:10:44 by lebroue          ###   ########.fr       */
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


int	handle_parent_builtins(t_data *data, t_cmd *curr, char *input)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(curr->name, "exit", 5))
	{
		if (apply_redirections(curr) == -1)
		{
			free_all(data, 1, NULL);
			exit(1);
		}
		ret = exec_builtins(curr, data, data->envp, input);
		free_all(data, ret, NULL);
	}
	if (!ft_strncmp(curr->name, "cd", 2)
		|| !ft_strncmp(curr->name, "export", 6)
		|| !ft_strncmp(curr->name, "unset", 5))
	{
		ret = exec_builtins(curr, data, data->envp, input);
		return (ret);
	}
	return (-1); // signifie : pas de builtin parent géré ici
}



void handle_child_process(t_data *data, t_cmd *curr, t_pipe *p, char *input)
{
    int ret = 0;

    if (p->prev_fd != -1)
    {
        dup2(p->prev_fd, STDIN_FILENO);
        close(p->prev_fd);
    }

    if (curr->next)
    {
        close(p->pipe_fd[0]);
        dup2(p->pipe_fd[1], STDOUT_FILENO);
        close(p->pipe_fd[1]);
    }

    if (apply_redirections(curr) == -1)
    {
        free_all(data, 1, NULL);
        exit(1);
    }

    if (is_builtins(curr->name))
    {
        ret = exec_builtins(curr, data, data->envp, input);
        free_all(data, ret, NULL);
        exit(ret);
    }

    curr->path = get_path(data->envp, curr->args[0], &ret);
    if (!curr->path)
    {
        write(2, "Command not found: ", 19);
        write(2, curr->args[0], strlen(curr->args[0]));
        write(2, "\n", 1);
        free_all(data, 127, NULL);
        exit(127);
    }

    close(data->saved_stdin);
    close(data->saved_stdout);
    execve(curr->path, curr->args, data->envp);
    perror("execve");
    free_all(data, 1, NULL);
    exit(1);
}




////////////////////////////////////////////////////////////////////////////
static void	handle_parent_process(t_cmd **curr, int *prev_fd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if ((*curr)->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	*curr = (*curr)->next;
}



int	execute_pipeline(t_data *data, t_cmd *curr, char *input)
{
	int		ret;
	int		prev_fd;
	int		status;
	pid_t	pid;
	int		pipe_fd[2];
	t_pipe p;

	ret = 0;
	prev_fd = -1;
	status = 0;
	while (curr)
	{
		if (curr->next && pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
			handle_child_process(data, curr, &p, input);
		handle_parent_process(&curr, &prev_fd, pipe_fd);
	}
	ret = waiting(pid, status);
	return (ret);
}


int	exec_cmd(t_data *data, char *input)
{
	int		ret;
	int		single_ret;
	t_cmd	*curr;

	ret = 0;
	curr = data->cmds;
	
	update_envp(data);

	if (is_single_cmd(data))
	{
		single_ret = handle_parent_builtins(data, curr, input);
		if (single_ret != -1)
			return (single_ret);
	}

	ret = execute_pipeline(data, curr, input);
	return (ret);
}

// int	exec_cmd(t_data *data, char *input)
// {
// 	int		ret;
// 	t_cmd	*curr;
// 	int		prev_fd;
// 	int		status;
// 	int single_ret; 

// 	pid_t pid;         // PID du processus enfant
// 	int pipe_fd[2];    // Tableau pour les pipes [0]=lecture, [1]=écriture
// 	ret = 0;           // Code de retour de la commande
// 	curr = data->cmds; // Commande courante
// 	prev_fd = -1;      // FD du pipe précédent pour la redirection stdin
// 	status = 0;
// 	// Statut utilisé pour récupérer le code de sortie des enfants
// 	update_envp(data); // Met à jour le tableau envp à partir de t_data
// 	if (is_single_cmd(data))
// 	{
// 		single_ret = handle_parent_builtins(data, curr, input);
// 		if (single_ret != -1)
// 			return (single_ret);
// 	}
// 	while (curr)
// 	{
// 		// Création du pipe si ce n'est pas la dernière commande
// 		if (curr->next && pipe(pipe_fd) == -1)
// 		{
// 			perror("pipe");
// 			return (1);
// 		}
// 		// Fork pour créer un enfant qui exécutera la commande
// 		pid = fork();
// 		if (pid < 0) // Erreur de fork
// 		{
// 			perror("fork");
// 			return (1);
// 		}
// 		else if (pid == 0) // Bloc enfant
// 		{
// 			// Si on a un pipe précédent, rediriger stdin
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd); // Fermeture du fd après duplication
// 			}
// 			// Si ce n'est pas la dernière commande,
// 			// rediriger stdout vers le pipe
// 			if (curr->next)
// 			{
// 				close(pipe_fd[0]); // On ferme le côté lecture
// 				dup2(pipe_fd[1], STDOUT_FILENO);
// 				// Redirige stdout vers l'écriture du pipe
// 				close(pipe_fd[1]); // Fermeture après duplication
// 			}
// 			// Appliquer les redirections (> < >> ...)
// 			if (apply_redirections(curr) == -1)
// 			{
// 				free_all(data, 1, NULL); // Libère la mémoire et met ret=1
// 				exit(1);                 // Sort de l'enfant
// 			}
// 			// Si la commande est un builtin dans un pipeline
// 			if (is_builtins(curr->name))
// 			{
// 				// printf("bonjour\n");
// 				ret = exec_builtins(curr, data, data->envp, input);
// 				// reset_std_in_out(data);
// 				free_all(data, ret, NULL); // Libération mémoire
// 											// Retourne le code de sortie du builtin
// 			}
// 			// Commande externe
// 			curr->path = get_path(data->envp, curr->args[0], &ret);
// 			if (!curr->path)
// 			{
// 				write(2, "Command not found: ", 19);
// 				write(2, curr->args[0], strlen(curr->args[0]));
// 				write(2, "\n", 1);
// 				free_all(data, 127, NULL);
// 				exit(127); // Code 127 pour commande non trouvée
// 			}
// 			close(data->saved_stdin);
// 			close(data->saved_stdout);
// 			// Exécuter la commande externe
// 			execve(curr->path, curr->args, data->envp);
// 			perror("execve"); // Si execve échoue
// 			free_all(data, 1, NULL);
// 			exit(1);
// 		}
// 		// Bloc parent : fermer les fd inutiles pour éviter les fuites
// 		if (prev_fd != -1)
// 			close(prev_fd);
// 		if (curr->next)
// 		{
// 			close(pipe_fd[1]); // Fermeture côté écriture
// 			prev_fd = pipe_fd[0];
// 			// On garde le côté lecture pour la prochaine commande
// 		}
// 		// Passer à la commande suivante dans la pipeline
// 		curr = curr->next;
// 	}
// 	// Parent attend tous les enfants pour récupérer leurs codes de sortie
// 	ret = waiting(pid, status);
// 	// Récupérer le code de sortie du dernier processus
// 	return (ret);
// }