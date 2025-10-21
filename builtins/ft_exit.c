
#include "../includes/minishell.h"


long long ft_atoll(const char *str)
{
    int i = 0;
    int sign = 1;
    long long result = 0;

    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = 10 * result + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

bool isnumber(const char *str)// CHECK SI LE NOMBRE EST VALIDE
{
    int i;
    int nb_start;
    const char *nb;
    int sign;

    i = 0;
    if (!str || !*str) // secu de str == NULL
        return false;
    skip_white_spaces(str, &i);
    sign = get_sign(str, &i);
    nb_start = i; // point de départ du nombre
    if (!check_if_only_digits(str, nb_start)) // check si tout est digit
        return (false);
    nb = &str[nb_start]; 
    nb = skip_zero_at_begining(nb); // skip les 0 devant
    if (!check_len_and_limits(nb, sign)) // check taille et valeur max/min
        return (false);
    return (true);
}

int ft_exit(char **args)
{
    long long nb;

    if (args[1])
    {
        if (!isnumber(args[1]))
        {
            printf("bash: exit: %s: numeric argument required\n", args[1]);
            return (2); //retour en priorite si l'argument n'est pas numeric
        }
        if (args[2])
        {
            printf("bash: exit: too many arguments\n");
            return (-12); // trop  d'arguments
        }
        nb = ft_atoll(args[1]);
        return (nb); // sort avec la valeur parser 
    }
    return (errno);
}


////IL Y A 8 FONCTIONS, IL FAUT ECLATER LES UTILS DE EXIT EN ft_exit_utils.c   : OK DONE

/*!!!!!GERER LE RETOUR D'ERREUR DE EXIT CORRECT SUR LA DERNIERE COMMANDE RECU!!!!!*/

/* 1er cas : "exit jhdsjhfdsjhf dsjhfdsjfjdsfhds"      : OK DONE 
bash: exit: jhdsjhfdsjhf: numeric argument required 
echo $? =2
*/

/* 2eme cas : "exit 15 fdfds"     :   OK DONE MAINTENANT IL EXIT
exit
bash: exit: too many arguments 
N'EXIT PAS
*/

/* 3eme cas : "exit [nbr]"
exit
echo $? = [nbr]
*/

//9223372036854775807 = int64_MAX                                  : OK DONE C'EST REGLER
/*4eme cas : exit [nbr > 64-bit signed integer ou nbr < 64-bit signed integer]
exit
bash: exit: 4444444444444444444444444444: numeric argument required
echo $? = 2
*/

/*5eme cas : exit
exit
echo $? = 0
*/

/*Si le 1er argument n'est pas numerique (qu'importe le nombre d'argument total) alors bash executera comme le 1er cas*/
/*Si le 1er argument est numerique MAIS QUE LE NBR D'ARGUMENT EST >= 2 alors bash executera comme le 2eme cas 
(peu importe ce que le 2eme argument represente)*/