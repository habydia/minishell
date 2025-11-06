/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:14:33 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/06 20:27:56 by lebroue          ###   ########.fr       */
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

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while (env[i])
	{
		if (ft_strsearch(env[i], '='))
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
