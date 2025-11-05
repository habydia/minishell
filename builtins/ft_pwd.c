/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:12:24 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/05 02:23:57 by lebroue          ###   ########.fr       */
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
		return (1);
	}
	write(1, buff, strlen(buff));
	free(buff);
	return (0);
}
