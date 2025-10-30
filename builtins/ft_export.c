/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:57:14 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/30 23:17:42 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void print_env_in_order(char **env)
	//doit print l'env dans l'ordre alphabetique
// {
// }
static bool identifier_correct(char *str)
{
	int i = 0;

	if (!str || !*str)
		return false;

	// Premier caractère : lettre ou '_'
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return false;
	i++;

	// Les suivants jusqu'à '=' : lettres, chiffres ou '_'
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return false;
		i++;
	}

	return true;
}


void	add_in_env(char *str, char **env)
{
	char	*key;
	char	*value;
	char	*new_entry;
	int		i;
	size_t	key_len;
	size_t	value_len;
	char	*eq_pos;

	i = 0;
	eq_pos = ft_strchr(str, '=');
	if (!eq_pos)
		return ;
	key_len = eq_pos - str;
	key = ft_strndup(str, key_len);
	value = ft_strdup(eq_pos + 1);
	while (env[i] && ft_strncmp(key, env[i], key_len) != 0)
		i++;
	value_len = ft_strlen(value);
	new_entry = malloc(key_len + 1 + value_len + 1); // clé + '=' + valeur+ '\0'
	if (!new_entry)
	{
		free(key);
		free(value);
		return ;
	}
	ft_strlcpy(new_entry, key, key_len + 1);
	new_entry[key_len] = '=';
	ft_strlcpy(new_entry + key_len + 1, value, value_len + 1);
	free(env[i]);
	env[i] = new_entry;
	env[i + 1] = NULL;
	free(key);
	free(value);
}

int	ft_export(char **str, char **env)
{
	int		i;

	i = 0;
	if (str[1] == NULL)
	{
		while (env[i])
		{
			write(1, "export ", 7);
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
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
		write(2, "bash: export: `", 15);
		write(2, str[1], ft_strlen(str[1]));
		write(2, "': not a valid identifier\n", 25);
		errno = 1;
	}
	return (0);
}

// appeler export sans argument va print l'env dans l'ordre ALPHABETIQUE DE L'ascii (MAJ EN PREMIER PUIS minuscule)

// pour qu'un export sois correct, need que lettres et le '='