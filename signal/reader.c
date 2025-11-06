/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:42:00 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/05 15:51:01 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signals.h"

char	*reader(void)
{
	char	*line;

	line = readline("Minishell> ");
	if (line == NULL)
		exit(1);
	if (!line)
	{
		perror("Error reading line");
		return (NULL);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
