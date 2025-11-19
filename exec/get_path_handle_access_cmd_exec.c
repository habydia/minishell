/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_handle_access_cmd_exec.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 02:36:41 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 00:17:15 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*directory_error_messsage(const char *argv_cmd, int *ret)
{
	write(2, argv_cmd, ft_strlen(argv_cmd));
	write(2, ": is a directory\n", 17);
	*ret = 126;
	return (NULL);
}

char	*access_error_message(const char *argv_cmd, int *ret)
{
	write(2, argv_cmd, ft_strlen(argv_cmd));
	write(2, ": Permission denied\n", 20);
	*ret = 126;
	return (NULL);
}

char	*strdup_error_message(int *ret)
{
	perror("malloc");
	*ret = 1;
	return (NULL);
}

char	*if_no_argv_cmd(int *ret)
{
	*ret = 1;
	return (NULL);
}

char	*handle_access_cmd(char *argv_cmd, int *ret)
{
	char	*result;

	if (!argv_cmd)
		return (if_no_argv_cmd(ret));
	if (ft_strchr(argv_cmd, '/'))
	{
		if (access(argv_cmd, F_OK) != 0)
		{
			*ret = 127;
			return (NULL);
		}
		if (check_if_is_a_directory(argv_cmd))
			return (directory_error_messsage(argv_cmd, ret));
		if (access(argv_cmd, X_OK) != 0)
			return (access_error_message(argv_cmd, ret));
		result = ft_strdup(argv_cmd);
		if (!result)
			return (strdup_error_message(ret));
		*ret = 0;
		return (result);
	}
	*ret = 0;
	return (NULL);
}
