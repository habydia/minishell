/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:50:38 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/14 14:57:02 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool	check_if_to_many_arguments(char **args)
{
	if (args[1])
	{
		if (args[2])
		{
			write(2, "cd: too many arguments\n", 24);
			return (true);
		}
	}
	return (false);
}

bool	check_directory_path_size_limit(char *path, size_t limit)
{
	if (ft_strlen(path) > limit)
	{
		write(2, "Minishell: cd: File name too long\n", 34);
		return (true);
	}
	return (false);
}

bool	check_chdir(int ret)
{
	if (ret == -1)
	{
		perror("cd");
		return (true);
	}
	return (false);
}

bool	check_path_is_valid(char *path, size_t limit)
{
	if (check_directory_path_size_limit(path, limit) == true)
	{
		free(path);
		return (false);
	}
	return (true);
}
