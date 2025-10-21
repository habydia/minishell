
#include "../includes/minishell.h"

int ft_unset(char **str, char **env)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (str[1] == NULL)
        return (0);
    while (str[++i])
    {
        if (ft_strchr(str[i], '=') == NULL)
        {
            while (env[j])
            {
                if (ft_strncmp(env[j], str[i], ft_strlen(str[i])) == 0)
                    break ;
                j++;
            }
            if (env[j])
                free(env[j]);
            env[j] = NULL;
        }
    }
    return (0);
}
