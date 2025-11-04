/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:38:29 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/04 23:05:02 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_cd(char **args)
{
	char	*path;
	int		ret;
	size_t	limit;

	limit = 255;
	if (args[2]) // trop d'arguments ?
	{
		write(2, "cd: too many arguments\n", 24);
		return (1);
	}
	if (!args[1] || (args[1][0] == '~' && (args[1][1] == '\0'
				|| args[1][1] == '/')))
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
	if (strlen(path) > limit)
	{
		write(2, "cd: File name too long\n", 24);
		return (1);
	}
	ret = chdir(path);
	if (ret == -1)
	{
		perror("cd"); 
		return (1);
	}
	return (0);
}
