/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:29:28 by lebroue           #+#    #+#             */
/*   Updated: 2025/10/31 16:38:13 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../include/parsing.h"

/*
static int	lstsize_env(t_env *envd)
{
	int	i;

	i = 0;
	if (!envd)
	return (0);
	while (envd)
	{
		envd = envd->next;
		i++;
	}
	return (i);
}
*/

void	free_lst_env(t_env **envd, bool ext, int errcode)
{
	t_env	*tmp;

	if (!(*envd))
		return ;
	while (*envd)
	{
		tmp = (*envd)->next;
		if ((*envd)->key)
			free((*envd)->key);
		if ((*envd)->value)
			free((*envd)->value);
		free(*envd);
		*envd = tmp;
	}
	if (ext)
		exit(errcode);
}

t_env	*ft_lstlast_env(t_env *envd)
{
	if (!envd)
		return (envd);
	while (envd->next)
		envd = envd->next;
	return (envd);
}

int	add_back_env(t_env **envd)
{
	t_env	*node;
	t_env	*tmp;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (1);
	node->next = NULL;
	if (!*envd)
		*envd = node;
	else
	{
		tmp = ft_lstlast_env(*envd);
		tmp->next = node;
	}
	return (0);
}
