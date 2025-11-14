/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:41:40 by hadia             #+#    #+#             */
/*   Updated: 2025/11/14 23:27:33 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_syntax_token(t_token_type type)
{
	return (type == T_PIPE || type >= T_REDIR_IN);
}

static int	pipe_error(t_token *current, t_token *prev)
{
	if (current->type == T_PIPE)
	{
		if (!prev || prev->type == T_PIPE)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	syntax_errors(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens)
		return (0);
	current = tokens;
	prev = NULL;
	while (current && current->type != T_EOF)
	{
		if (pipe_error(current, prev))
			return (1);
		if (is_syntax_token(current->type) && current->next
			&& current->next->type == T_EOF)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
