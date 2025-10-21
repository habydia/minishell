
#include "../includes/minishell.h"

static int	strsearch(const char *str, int c)
{
	int				i;
	unsigned char	tmp;

	i = 0;
	tmp = (unsigned char)c;
	while (str[i])
	{
		if (tmp == (unsigned char)str[i])
			return (1);
		i++;
	}
	if (tmp == '\0')
		return (0);
	return (0);
}

void	ft_env(char **env)
		// Pour le moment prototyper en void(char **env) <------- Surement a changer !
{
	int i = 0;
	while (env && env[i])
	{
		if (strsearch(env[i], '=') == 1)
			printf("%s\n", env[i]);
		i++;
	}
}

// IL FAUDRA DUPLIQUER L'ENV PARENT ET TRAVAILLER DESSUS !