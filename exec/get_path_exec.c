/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:33:52 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_is_a_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

char	*check_is_access_and_is_directory(char *new_path, int *ret)
{
	if (access(new_path, F_OK) != 0)
		return (NULL);
	if (check_if_is_a_directory(new_path))
	{
		write(2, new_path, ft_strlen(new_path));
		write(2, ": is a directory\n", 17);
		*ret = 126;
		return (NULL);
	}
	if (access(new_path, X_OK) != 0)
	{
		write(2, new_path, ft_strlen(new_path));
		write(2, ": Permission denied\n", 20);
		*ret = 126;
		return (NULL);
	}
	*ret = 0;
	return (new_path);
}

char	*free_paths_and_return(char *result, char **paths)
{
	ft_free_tab_str(paths);
	return (result);
}

char	*get_path_in_paths_list(char **paths, int *ret, char *buffer,
		char *argv_cmd)
{
	char	*new_path;
	char	*result;
	int		i;

	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		buffer = ft_strjoin(paths[i], "/");
		if (!ft_strjoin_checker(buffer, NULL, paths, ret))
			return (NULL);
		new_path = ft_strjoin(buffer, argv_cmd);
		if (!ft_strjoin_checker(new_path, buffer, paths, ret))
			return (NULL);
		free(buffer);
		result = check_is_access_and_is_directory(new_path, ret);
		if (result)
			return (free_paths_and_return(result, paths));
		free(new_path);
	}
	ft_free_tab_str(paths);
	*ret = 127;
	return (NULL);
}

char	*get_path(char **envp, char *argv_cmd, int *ret)
{
	char	*path;
	char	**paths;
	char	*buffer;

	buffer = NULL;
	if (!argv_cmd)
	{
		*ret = 1;
		return (NULL);
	}
	buffer = handle_access_cmd(argv_cmd, ret);
	if (buffer)
		return (buffer);
	if (*ret != 0)
		return (NULL);
	path = envp_search(envp);
	if (path_check(path, ret) == 1)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
	{
		*ret = 1;
		return (NULL);
	}
	return (get_path_in_paths_list(paths, ret, buffer, argv_cmd));
}
