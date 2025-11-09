/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:38:29 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/09 15:58:21 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*cd_get_path(char **args)
{
	char	*path;
	char	*home;

	if (!args[1] || (args[1][0] == '~' && (args[1][1] == '\0'
		|| args[1][1] == '/')))
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
		path = ft_strdup(home);
	}
	else
		path = ft_strdup(args[1]);
	if (!path)
		perror("cd: malloc");
	return (path);
}

int	ft_cd(char **args)
{
	char	*path;
	int		ret;
	size_t	limit;

	limit = 255;
	if (check_to_many_arguments(args) == true)
		return (1);
	path = cd_get_path(args);
	if (!path)
		return (1);
	if (!check_path_validity(path, limit))
		return (1);
	ret = chdir(path);
	free(path);
	if (check_chdir(ret) == true)
		return (1);
	return (0);
}
