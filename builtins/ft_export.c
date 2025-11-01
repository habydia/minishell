/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:57:14 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/31 16:16:28 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Vérifie si un identifiant est valide pour export (avant le '=')
static bool	identifier_correct(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	// Premier caractère : lettre ou '_'
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	// Les suivants jusqu'à '=' : lettres, chiffres ou '_'
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

// Ajoute ou remplace une variable dans l'environnement
void	add_in_env(char *str, char **env)
{
	char	*eq_pos;
	char	*new_entry;
	char	*value;
	char	*key;
	int		i;

	i = 0;
	eq_pos = ft_strchr(str, '=');
	if (!eq_pos)
		return ;
	key = ft_strndup(str, eq_pos - str); // Clé avant '='
	value = ft_strdup(eq_pos + 1);      
		// Valeur après '='// Cherche si la clé existe déjà
	while (env[i] && ft_strncmp(key, env[i], eq_pos - str) != 0)
		i++;
	new_entry = malloc(ft_strlen(key) + 1 + ft_strlen(value) + 1);
		// Crée la nouvelle entrée "key=value"
	if (!new_entry)
	{
		free(key);
		free(value);
		return ;
	}
	ft_strlcpy(new_entry, key, ft_strlen(key) + 1);
	new_entry[ft_strlen(key)] = '=';
	ft_strlcpy(new_entry + ft_strlen(key) + 1, value, ft_strlen(value) + 1);
	if (env[i]) // Remplace si existe, sinon ajoute
		free(env[i]);
	env[i] = new_entry;
	if (!env[i + 1]) // Assure que le tableau reste NULL-terminé
		env[i + 1] = NULL;
	free(key);
	free(value);
}

int	ft_export(char **args, char **env)
{
	int	i;

	i = 0;
	if (!args[1]) // Si aucun argument, affiche l'env
	{
		while (env[i])
		{
			write(1, "export ", 7);
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
			i++;
		}
		return (0);
	}
	i = 0;
	while (args[++i]) // Traite chaque argument
	{
		if (!identifier_correct(args[i]))
		{
			// Identifiant invalide
			write(2, "minishell: export: `", 21);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 25);
			errno = 1;
		}
		else
		{
			// Ajoute ou remplace dans env si '=' présent
			if (ft_strchr(args[i], '='))
				add_in_env(args[i], env);
		}
	}
	return (0);
}

// appeler export sans argument va print l'env dans l'ordre ALPHABETIQUE DE L'ascii (MAJ EN PREMIER PUIS minuscule)

// pour qu'un export sois correct, need que lettres et le '='