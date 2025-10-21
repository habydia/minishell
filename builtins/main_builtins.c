
#include "../includes/minishell.h"

// void free_tab(char **str)
// {
// 	int i;

// 	i = 0;
// 	while(str && str[i])
// 		free(str[i++]);
// 	free(str);
// }
// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	char *input;
// 	char **str;
	
// 	while(1)
// 	{
// 		input = readline("> ");
// 		if (*input)
// 		add_history(input);
// 		str = ft_split(input, ' ');
// 		if (!str)
// 			return (free(input), 0);
// 		exec_builtins(str, env, input);
// 		free(input);
// 		free_tab(str);
// 	}
// 	return (0);
// }

/* pour le moment pwd marche, a revoir lorsqu'on aura le cd. Il faudra peut etre une fonction qui lancera
tous les builtins pour eviter de saccager le main. ERRNO -12 permet de ne pas exit dans la fonction ft_exit.
!!!!!!!! MAIN TEMPORAIRE !!!!!!!!! */

//EXIT EST GLOBALEMENT FONCTIONNEL, NEED GERER L'OVERFLOW/UNDERFLOW ET DEVOIR LE RESTRUCTURER PAR LA SUITE,
//(avec une structure, sa sera plus facile de tout free directement dans ft_exit pour exit direct dedans)!

//NEED SECURE SUR TOUT LES BUILTINS, REMONTER D'ERREUR ETC.


