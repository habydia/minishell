#include "minishell_signals.h"

char	*reader(void)
{
	char *line;

	line = readline("Minishell> ");
	if (line == NULL)
		exit(0);
	if (!line)
	{
		perror("Error reading line");
		return (NULL);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}