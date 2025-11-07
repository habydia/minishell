/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:42:00 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/07 02:55:23 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signals.h"
#include "env.h"

char	*reader(t_data *data)
{
	char	*line;

	line = readline("Minishell> ");
	if (line == NULL)
		free_all(data, 1, NULL);
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
