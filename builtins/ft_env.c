/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:14:33 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/08 19:10:42 by lebroue          ###   ########.fr       */
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

int	ft_env(char **args, char **env)
{
	int	i;

	i = 0;
	if (args[1])
	{
		write(2, "env: No such file or directory\n", 31);
		return (1);
	}
	if (!env)
		return (1);
	while (env[i])
	{
		if (ft_strsearch(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
