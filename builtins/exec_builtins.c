
#include "../includes/minishell.h"

void	exec_builtins(t_exec *exec, char **env, char *input)
		// envoie de t_data pour remonter d'erreur et free si ca crash
{
	while (exec && exec->cmd)
	{
		if (ft_strncmp(exec->cmd[0], "env", 3) == 0
			&& ft_strlen(exec->cmd[0]) == 3)
			ft_env(env);
		else if (ft_strncmp(exec->cmd[0], "pwd", 3) == 0
			&& ft_strlen(exec->cmd[0]) == 3)
			ft_pwd();
		else if (ft_strncmp(exec->cmd[0], "exit", 4) == 0
			&& ft_strlen(exec->cmd[0]) == 4)
		{
			errno = ft_exit(exec->cmd);
			if (errno != -12)
				/// a changer car on peux pas set errno en retour de int  donc modifier cette partie qui est fausse
			{
				free(input);
				free_tab(exec->cmd);
				exit(errno);
			}
		}
		else if (ft_strncmp(exec->cmd[0], "echo", 4) == 0
			&& ft_strlen(exec->cmd[0]) == 4)
			ft_echo(exec->cmd);
		else if (ft_strncmp(exec->cmd[0], "cd", 2) == 0
			&& ft_strlen(exec->cmd[0]) == 2)
			ft_cd(exec->cmd);
		else if (ft_strncmp(exec->cmd[0], "export", 6) == 0
			&& ft_strlen(exec->cmd[0]) == 6)
			ft_export(exec->cmd, env);
		else if (ft_strncmp(exec->cmd[0], "unset", 5) == 0
			&& ft_strlen(exec->cmd[0]) == 5)
			ft_unset(exec->cmd, env);
		else
		{
			printf("bash %s: command not found\n", input);
			errno = 127; // est-ce correct ?
		}
		exec = exec->next;
	}
}

/*Parcourir ta liste chaine pour trouver les builtins*/ // DONE