/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:57:14 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/04 02:52:11 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// Ajoute ou met à jour une variable dans la liste chaînée
void add_or_update_env(t_env **env, char *str)
{
    char *eq_pos;
    char *key;
    char *value;
    t_env *tmp;
	
	eq_pos = ft_strchr(str, '=');
	value = NULL;
	tmp = *env;
    if (eq_pos)
    {
        key = ft_strndup(str, eq_pos - str);
        value = ft_strdup(eq_pos + 1);
    }
    else
        key = ft_strdup(str);

    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key))
        {
            
            if (value)// Mise à jour uniquement si on a une valeur
            {
                free(tmp->value);
                tmp->value = value;
            }
            else
                free(key); // rien à mettre à jour si pas de '='
            return;
        }
        tmp = tmp->next;
    }

    // Si pas trouvé, ajouter à la fin
    t_env *new_node;
	new_node  = malloc(sizeof(t_env));
    if (!new_node)
    {
        free(key);
        if (value)
            free(value);
        return;
    }
    new_node->key = key;
    new_node->value = value; // peut être NULL si pas de '='
    new_node->next = NULL;

    if (!*env)
        *env = new_node;
    else
    {
        tmp = *env;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}

// Vérifie si un identifiant est valide pour export (uniquement la clé avant '=')
static bool identifier_correct(char *str)
{
    int i;
    char *eq_pos;
	int len;
	
	eq_pos = ft_strchr(str, '=');
	i = 1;
	if (eq_pos) // si '=' existe dans la chaîne
    	len = eq_pos - str; // longueur de la clé = distance entre le début et '='
	else
    	len = ft_strlen(str); // sinon, la clé fait toute la longueur de la chaîne
    if (len == 0)
        return (false);
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (false);

    while (i < len)
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return false;
        i++;
    }
    return true;
}

// Fonction principale export
int ft_export(char **args, char **env, t_data *data)
{
    int i;
    int exit_code;
	
	i = 0;
	exit_code = 0;
    if (!args[1]) // Aucun argument : afficher l'environnement
    {
        i = 0;
        while (env[i])
        {
            write(1, "export ", 7);
            write(1, env[i], ft_strlen(env[i]));
            write(1, "\n", 1);
            i++;
        }
        return (0);
    }
    while (args[++i])
    {
        char *key_only;
        char *eq_pos;
		int key_len;
				
		eq_pos = ft_strchr(args[i], '=');
		if (eq_pos != NULL)
		{
    		key_len = eq_pos - args[i];  // longueur de la clé
    		key_only = ft_strndup(args[i], key_len);
		}
else
{
    key_only = ft_strdup(args[i]);  // pas de '=', on prend toute la chaîne
}


        if (!identifier_correct(key_only))
        {
            write(2, "export: `", 9);
            write(2, args[i], ft_strlen(args[i]));
            write(2, "': not a valid identifier\n", 28);
            exit_code = 1;
        }
        else
        {
            add_or_update_env(&data->env, args[i]);
        }
        free(key_only);
    }

    update_envp(data); // Reconstruit data->envp après tous les ajouts
    return exit_code;
}
