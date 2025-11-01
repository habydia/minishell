/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:38:29 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/31 15:16:38 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//attention modifier dans le parsing "~" toute seul pour que ca revienne sur HOME.

int	ft_cd(char **args)
{
	char	*path;
	int		ret;
	size_t	limit;

	limit = 255;
	if (args[2]) // trop d'arguments ?
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (!args[1] || (args[1][0] == '~' && (args[1][1] == '\0'
				|| args[1][1] == '/'))) // chemin par défaut ~ ou ~/ → HOME
	{
		path = getenv("HOME");
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
	}
	else
		path = args[1];
	if (strlen(path) > limit) // limite de longueur
	{
		write(2, "cd: File name too long\n", 24);
		return (1);
	}
	ret = chdir(path);
	if (ret == -1)
	{
		perror("cd"); // affiche automatiquement le message système lié à errno
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
//	- gerer le cd ~\      | ouvre un heredoc et verifie si le directory ~EOF existe | Exemple : cd ~\   > yo  ==> minishell: cd: ~yo: No such file or directory