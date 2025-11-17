/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:35:05 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/17 23:03:35 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_array_lines(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static int	parse_n_flags(char **str, int *i)
{
	int	detect_n_flag;
	int	j;

	detect_n_flag = 0;
	while (str[*i] && str[*i][0] == '-' && str[*i][1])
	{
		j = 1;
		while (str[*i][j] == 'n')
			j++;
		if (str[*i][j] == '\0')
		{
			detect_n_flag = 1;
			(*i)++;
			continue ;
		}
		break ;
	}
	return (detect_n_flag);
}

int	ft_echo(char **str)
{
	int		i;
	int		detect_n_flag;
	size_t	count;

	i = 1;
	detect_n_flag = 0;
	count = count_array_lines(str);
	(void)count;
	detect_n_flag = parse_n_flags(str, &i);
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!detect_n_flag)
		printf("\n");
	return (0);
}
