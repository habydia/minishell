/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:16:36 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/03 20:50:24 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "exec.h"

int	ft_atoi(const char *str)
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

bool	isnumber(const char *str) // CHECK SI LE NOMBRE EST VALIDE
{
	int i;
	int nb_start;
	const char *nb;
	int sign;

	// printf("input: '%s'\n", str);
	i = 0;
	if (!str || !*str) // secu de str == NULL
		return (false);
	sign = get_sign(str, &i);
	nb_start = i;                             // point de depart
	if (!check_if_only_digits(str, nb_start)) // check si tout est digit
		return (false);
	nb = &str[nb_start];
	nb = skip_zero_at_begining(nb);      // skip les 0 devant
	if (!check_len_and_limits(nb, sign)) // check taille et valeur max/min
		return (false);
	return (true);
}

int	ft_exit(char **args, t_data *data)
{
	long long	nb;

	nb = 0;
	write(1, "exit\n", 5); // affiche "exit" sur stdout
	if (args[1])
	{
		if (!isnumber(args[1]))
		{
			write(2, "minishell: exit: ", 18);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 27);
			nb = 2;
		}
		if (args[2])
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			nb = 2;
		}
		else
			nb = ft_atoi(args[1]);
	}
	// 🔹 Libération mémoire
	free_envp(data->envp);
	free_cmds(data->cmds);
	free_lst_env(&data->env, false, 0);
	// return (0); // exit sans argument : code de retour par défaut
	exit((int)(nb % 256)); // code de retour modulo 256
}

////IL Y A 8 FONCTIONS,
// IL FAUT ECLATER LES UTILS DE EXIT EN ft_exit_utils.c : OK DONE

/*!!!!!GERER LE RETOUR D'ERREUR DE EXIT CORRECT SUR LA DERNIERE COMMANDE RECU!!!!!*/

/* 1er cas : "exit jhdsjhfdsjhf dsjhfdsjfjdsfhds"      : OK DONE
minishell: exit: jhdsjhfdsjhf: numeric argument required
echo $? =2
*/

/* 2eme cas : "exit 15 fdfds"     :   OK DONE MAINTENANT IL EXIT
exit
minishell: exit: too many arguments
N'EXIT PAS
*/

/* 3eme cas : "exit [nbr]"
exit
echo $? = [nbr]
*/

// 9223372036854775807 = int64_MAX                                  : OK DONE C'EST REGLER
/*4eme cas : exit [nbr > 64-bit signed integer ou nbr < 64-bit signed integer]
exit
minishell: exit: 4444444444444444444444444444: numeric argument required
echo $? = 2
*/

/*5eme cas : exit
exit
... (6lignes restantes)*/