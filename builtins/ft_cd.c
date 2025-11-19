/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:38:29 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 01:03:39 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		perror("cd: malloc");
		return (NULL);
	}
	return (path);
}

int	ft_cd(char **args)
{
	char	*path;
	int		ret;
	size_t	limit;

	limit = 255;
	if (check_if_to_many_arguments(args) == true)
		return (1);
	path = cd_get_path(args);
	if (!path)
		return (1);
	if (!check_path_is_valid(path, limit))
		return (1);
	ret = chdir(path);
	free(path);
	if (check_chdir(ret) == true)
		return (1);
	return (0);
}
