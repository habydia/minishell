/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_is_number_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:18:02 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/31 15:35:06 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "builtins.h"

int	get_sign(const char *str, int *i) // SKIP LES SIGNES ET VERIFIE LE SIGN
{
	int sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-') // skip si il y a u + ou un - est avance sur la string en
											// decalent le pointeur de i pour l'avoir a la bonne position
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

bool	check_if_only_digits(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i]) // il ne doit y avoir que des digits
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
const char	*skip_zero_at_begining(const char *nb)
{
	while (*nb == '0' && nb[1] != '\0')// skip les zéros,mais garde un seul zéro si suivis d'un '\0'
		nb++;
	return (nb);
}
bool	check_len_and_limits(const char *nb, int sign)
{
	int nb_len;

	nb_len = 0;
	while (ft_isdigit(nb[nb_len])) // calcule la longueur
		nb_len++;
	if (nb_len > 19) // trop long pour un long long
		return (false);
	if (nb_len == 19) // si pile la taille d’un long long il verifie que ca
						// n'overflow pas dans un long long int min ou max
	{
		if (sign == 1 && ft_strncmp(nb, INT64_MAX_STR, 19) > 0)
			return (false);
		if (sign == -1 && ft_strncmp(nb, INT64_MIN_STR, 19) > 0)
			return (false);
	}
	return (true);
}