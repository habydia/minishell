
#include "../includes/minishell.h"

int	ft_cd(char **str)
		// Prototypage qui sera changer par la suite. SECURE A FAIRE //
{
	char *path;
	int ret;
	size_t limit;
	int i;

	i = 0;
	limit = 255;
	while (str[1] && str[1][i] == ' ')
		i++;
	if (str[2] != NULL)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (str[1] == NULL || ft_strncmp(str[1], "~", 1) == 0 || (ft_strncmp(str[1],
				"~/", 2) == 0))
		// gere le ~ comme argument et ~/ pour aller  vers home
	{
		path = getenv("HOME");
		if (path == NULL)
			return (1);
	}
	else
		path = str[1];
	if (ft_strlen(path) > limit)
	{
		printf("cd: %s: File too long\n", path);
		return (1);
	}
	ret = chdir(path);
	if (ret == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

//  1 - si on ecrit cd et plains d'espaces,
//	la fonction est sence executer cd et renvoyer sur home.
//  2 - le deuxieme argument est vide mais plains d'espaces, alors,
//	prendre en compte que cd.
//  3
//	- Si ecrit cd                                                  ~ retour sur home.
//  4
//	- Si ecrit cd                                                    ~/ retour sur home.
//  5 - Gerer le cd .. ?
//  6
//	- gerer le cd ~\      | ouvre un heredoc et verifie si le directory ~EOF existe | Exemple : cd ~\   > yo  ==> bash: cd: ~yo: No such file or directory
