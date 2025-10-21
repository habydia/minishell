
#include "../includes/minishell.h"

void	ft_pwd(void)
		// Pour le moment prototyper en void(void) <------- Surement a
                  // changer !
{
  char *buff = getcwd(NULL, 0);
  if (buff == NULL)
    perror("pwd");
  printf("%s\n", buff);
  free(buff);
}

// marche mais la remonter d'erreur n'est pas faite !
// pwd marche meme si env est vide. il faudra stocker le pwd dans une variable
// d'environnement.