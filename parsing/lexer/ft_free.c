/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 03:22:13 by hadia             #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;
	t_token	*current;

	current = tokens;
	while (current)
	{
		temp = current->next;
		free(current->value);
		free(current);
		current = temp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		temp = current->next;
		free(current->name);
		free_args_on_error(current->args);
		free_redirs(current->redirs);
		free(current);
		current = temp;
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*current;
	t_redir	*temp;

	current = redirs;
	while (current)
	{
		temp = current->next;
		free(current->file);
		free(current);
		current = temp;
	}
}

void	free_args_on_error(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
