/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:57:49 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/30 22:16:31 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_unset(char **str, char **env)
{
	int i;// indice de l'argument passé à unset
    int j;// indice courant dans env pour chercher la variable à supprimer
    int k_len_for_next;// indice source pour décaler les éléments du tableau après suppression
      
	if (!str[1])
		return (0);
	i = 0;
	while (str[++i])
	{
		if (ft_strchr(str[i], '=') == NULL) // on ne touche pas aux variables avec '='
		{
			j = 0;
			while (env[j])
			{
				if (ft_strncmp(env[j], str[i], ft_strlen(str[i])) == 0
					&& (env[j][ft_strlen(str[i])] == '='
						|| env[j][ft_strlen(str[i])] == '\0'))
				{
					free(env[j]);
					k_len_for_next = j; // Décaler le reste du tableau vers la gauche
					while (env[k_len_for_next])
					{
						env[k_len_for_next] = env[k_len_for_next + 1];
						k_len_for_next++;
					}
					break ; // on passe à la prochaine variable à unset
				}
				j++;
			}
		}
	}
	return (0);
}
