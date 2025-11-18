/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 05:00:07 by hadia             #+#    #+#             */
/*   Updated: 2025/11/18 05:29:37 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	tokenize_operator(const char *line, int *i, int *start, t_token **tokens)
{
	t_token_type	type;
	char			*value;
	int				j;

	type = get_operator_type(line, i);
	value = malloc(*i - *start + 1);
	if (!value)
	{
		free_tokens(*tokens);
		return (0);
	}
	j = 0;
	while (j < *i - *start)
	{
		value[j] = line[*start + j];
		j++;
	}
	value[j] = '\0';
	if (!push_new_token(tokens, type, value))
	{
		free_tokens(*tokens);
		return (0);
	}
	return (1);
}

int	tokenize_quote(const char *line, int *start, int *i, t_token **tokens)
{
	char	*quoted_value;
	int		original_i;

	original_i = *i;
	if (!is_quote_balanced(line, *start, *i))
	{
		*i = original_i;
		free_tokens(*tokens);
		return (0);
	}
	quoted_value = malloc(*i - *start + 1);
	if (!quoted_value)
	{
		free_tokens(*tokens);
		return (0);
	}
	ft_strlcpy(quoted_value, line + *start, *i - *start + 1);
	if (!push_new_token(tokens, T_WORD, quoted_value))
	{
		free_tokens(*tokens);
		return (0);
	}
	return (1);
}

int	tokenize_word(int *start, int *i, t_token **tokens, const char *line)
{
	char	*word;
	int		j;

	word = malloc(*i - *start + 1);
	if (!word)
	{
		free_tokens(*tokens);
		return (0);
	}
	j = 0;
	while (j < *i - *start)
	{
		word[j] = line[*start + j];
		j++;
	}
	word[j] = '\0';
	if (!push_new_token(tokens, T_WORD, word))
	{
		free_tokens(*tokens);
		return (0);
	}
	return (1);
}

int	handle_quote(const char *line, int *i, int *start, t_token **tokens)
{
	char	quote_type;
	int		original_i;

	quote_type = line[*i];
	original_i = *i;
	*start = *i;
	if (!find_closing_quote(line, i, quote_type))
	{
		*i = original_i;
		while (line[*i] && !ft_isspace(line[*i]) && !is_operator_char(line[*i]))
			(*i)++;
	}
	if (!tokenize_quote(line, start, i, tokens))
		return (0);
	return (1);
}

int	handle_operator_and_quote(int *i, int *start, const char *line,
		t_token **tokens)
{
	if (is_operator_char(line[*i]))
	{
		if (!tokenize_operator(line, i, start, tokens))
			return (0);
	}
	else if (line[*i] == '"' || line[*i] == '\'')
	{
		if (!handle_quote(line, i, start, tokens))
			return (0);
	}
	return (1);
}
