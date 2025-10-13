#include "include/minishell_signals.h"
#include "include/parsing.h"

int	main(int ac, char **av)
{
	char *line;
	t_cmd *cmds;

	(void)ac;
	(void)av;
	handle_signals();
	while (1)
	{
		line = reader();
		if (!line)
			continue ;
		cmds = parsing(line);

		if (!exec_cmd(NULL, cmds))
			perror("exec_cmd");

		free_cmds(cmds);
		free(line);
	}
	return (0);
}