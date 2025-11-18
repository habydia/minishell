/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 06:29:38 by hadia             #+#    #+#             */
/*   Updated: 2025/11/18 22:37:02 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	if (!value)
	{
		token->value = NULL;
		return (token);
	}
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

int	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return (0);
	if (!*tokens)
	{
		*tokens = new_token;
		return (1);
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (1);
}

int	push_new_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = create_token(type, value);
	free(value);
	if (!new_token)
		return (0);
	if (!add_token_back(tokens, new_token))
	{
		free(new_token->value);
		free(new_token);
		return (0);
	}
	return (1);
}
