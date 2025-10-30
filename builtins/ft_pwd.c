/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:12:24 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/30 21:41:23 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
	{
		perror("pwd");
		return (1); // code d'erreur standard
	}
	printf("%s\n", buff);
	free(buff);
	return (0);
}

// marche mais la remonter d'erreur n'est pas faite !
// pwd marche meme si env est vide. il faudra stocker le pwd dans une variable
// d'environnement.