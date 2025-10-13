#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	*cmds;
	t_env	*envd;
	t_data	data;

	envd = NULL;
	init_lst_env(&envd, env); // segfault
	(void)ac;
	(void)av;
	handle_signals();
	while (1)
	{
		line = reader();
		if (!line)
			continue ;
		if (line[0] != '\0')
			add_history(line);
		init_data(&data, &envd, NULL);
		cmds = parsing(line);
		print_cmds(cmds);
		// init_lst_exec
		exec_cmd(cmds, &data);
		free_cmds(cmds);
		free(line);
	}
	return (0);
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd *tmp;
	int i;

	tmp = cmds;
	while (tmp)
	{
		printf("Command: %s\n", tmp->name);
		if (tmp->args)
		{
			i = 0;
			printf("Arguments:\n");
			while (tmp->args[i])
			{
				printf("  arg[%d]: %s\n", i, tmp->args[i]);
				i++;
			}
		}
		else
		{
			printf("No arguments\n");
		}
		if (tmp->redirs)
		{
			t_redir *r_tmp = tmp->redirs;
			printf("Redirections:\n");
			while (r_tmp)
			{
				printf("  Type: %d, File: %s\n", r_tmp->type, r_tmp->file);
				r_tmp = r_tmp->next;
			}
		}
		else
		{
			printf("No redirections\n");
		}
		tmp = tmp->next;
	}
}