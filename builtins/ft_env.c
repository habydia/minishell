/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:14:33 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/31 13:34:37 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_strsearch(const char *str, int c)
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

int	ft_env(char **env)
{
	int	i;

	if (!env)
		return (1); // erreur : pas d'environnement c'est OK /

	i = 0;
	while (env[i])
	{
		if (ft_strsearch(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

// IL FAUDRA DUPLIQUER L'ENV PARENT ET TRAVAILLER DESSUS !