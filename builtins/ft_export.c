
#include "../includes/minishell.h"


// void print_env_in_order(char **env) //doit print l'env dans l'ordre alphabetique
// {
// }
static bool identifier_correct(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '=')
			i++;
		else
			return (false);
	}
	return (true);
}
void add_in_env(char *str, char **env) //ALL SECURE MALLOC A FAIRE
{
    char *key;
    char *value;
    int i;

    i = 0;
    key = ft_strndup(str, ft_strchr(str, '=') - str);
    value = ft_strdup(ft_strchr(str, '=') + 1);
    while (env[i] && ft_strncmp(key, env[i], ft_strlen(key)) != 0)
        i++;
    env[i] = ft_strjoin(key, "="); 
    env[i] = ft_strjoin(env[i], value);
    env[i + 1] = NULL;
    free(key);
    free(value);
}

int ft_export(char **str, char **env)
{
    int i;

    i = 0;
    if (str[1] == NULL)
    {
        while (env[i])
        {
            printf("export %s\n", env[i]);
            i++;
        }
    }
    else if (identifier_correct(str[1]))
    {
        while (str[++i])
        {
            if (ft_strchr(str[i], '='))
                add_in_env(str[i], env);
        }
	}	
	else
	{
		printf("bash: export: `%s': not a valid identifier\n", str[1]);
		errno = 1;
	}
    return (0);
}

//appeler export sans argument va print l'env dans l'ordre ALPHABETIQUE DE L'ascii (MAJ EN PREMIER PUIS minuscule)

//pour qu'un export sois correct, need que lettres et le '='
