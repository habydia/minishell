/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:16:36 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/18 23:01:32 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_secure(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		result = result * 10 + (str[i] - '0');
		if (sign * result > INT_MAX || sign * result < INT_MIN)
			return (0);
		i++;
	}
	return (sign * result);
}

bool	is_valid_number(const char *str)
{
	int			i;
	int			nb_start;
	const char	*nb;
	int			sign;

	i = 0;
	if (!str || !*str)
		return (false);
	sign = get_sign(str, &i);
	nb_start = i;
	if (!check_if_only_digits(str, nb_start))
		return (false);
	nb = &str[nb_start];
	nb = skip_zero_at_begining(nb);
	if (!check_len_and_limits(nb, sign))
		return (false);
	return (true);
}

int	ft_exit(char **args)
{
	unsigned long	nb;

	nb = 0;
	write(1, "exit\n", 5);
	if (args[1])
	{
		if (!is_valid_number(args[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 29);
			return (2);
		}
		if (args[2])
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			return (1);
		}
		else
			nb = ft_atoi_secure(args[1]);
	}
	return (nb % 256);
}
