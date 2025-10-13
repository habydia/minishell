#include "include/minishell.h"

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
		if (line[0] != '\0')
			add_history(line);
		cmds = parsing(line);
		exec_cmd(cmds, NULL);

		free_cmds(cmds);
		free(line);
	}
	return (0);
}