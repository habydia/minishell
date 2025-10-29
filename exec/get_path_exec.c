/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:33:52 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/29 15:03:41 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "env.h"
#include "parsing.h"
#include "exec.h"


char	*envp_search(char **envp)
{
	if (!envp || !*envp)
		return (NULL);
	while (*envp)
	{
		// printf("*envp=%s\n", *envp);
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

int	path_check(char *path, int *ret)
{
	if (path == NULL)
	{
		*ret = 127;
		return (1);
	}
	return (0);
}

int ft_strjoin_checker(char *buffer, char **paths, int *ret)
{
    if (!buffer)
		{
			ft_free_tab_str(paths);
			*ret = 1;
			return (0);
		}
    return(1);
}
/////////////////////////////////////////////
///////////////GET-PATH//////////////////////
//////////////////////////////////////////////
char	*get_path_in_paths_list(char **paths, int *ret, char *buffer,
		char *argv_cmd)
{
	char	*new_path;
	int		i;

	i = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		buffer = ft_strjoin(paths[i], "/");
        if(!ft_strjoin_checker(buffer, paths, ret))
            return(NULL);
		new_path = ft_strjoin(buffer, argv_cmd);
		free(buffer);
		if (!new_path)
		{
			ft_free_tab_str(paths);
			*ret = 1;
			return (NULL);
		}
		if (access(new_path, F_OK | X_OK) == 0)
		{
			ft_free_tab_str(paths);
			return (new_path);
		}
		free(new_path);
		i++;
	}
	ft_free_tab_str(paths);
	*ret = 127;
	return (NULL);
}
//////////////////////////////////////////////
/// GET PATH pour choper le path de chaque commandes, test l'excution
////////////////////////////////////////////
char	*get_path(char **envp, char *argv_cmd, int *ret)
{
	char	*path;
	char	**paths;
	char	*buffer;

	buffer = NULL;
	// printf("OKKKKKKKKKKKKKKKKKKKKKKK");
	if (!argv_cmd)
	{
		*ret = 1;
		return (NULL);
	}
	if (access(argv_cmd, F_OK | X_OK) == 0)
		return (ft_strdup(argv_cmd));
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
