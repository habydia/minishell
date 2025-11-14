/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 05:00:13 by hadia             #+#    #+#             */
/*   Updated: 2025/11/14 23:37:34 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_operator(const char *line, int *i, t_token **tokens)
{
	int	start;

	start = *i;
	if (!handle_operator_and_quote(i, &start, line, tokens))
		return (0);
	return (1);
}

static int	process_word(const char *line, int *i, t_token **tokens)
{
	int		start;
	char	quote;

	start = *i;
	while (line[*i])
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i] == quote)
				(*i)++;
		}
		else if (ft_isspace(line[*i]) || is_operator_char(line[*i]))
			break ;
		else
			(*i)++;
	}
	if (!tokenize_word(&start, i, tokens, line))
		return (0);
	return (1);
}

static int	process_token(const char *line, int *i, t_token **tokens)
{
	if (is_operator_char(line[*i]))
		return (process_operator(line, i, tokens));
	else
	{
	}
	return (process_word(line, i, tokens));
}

t_token	*tokenize_line(const char *line)
{
	t_token	*tokens;
	int		i;
	int		in_token;

	tokens = NULL;
	i = 0;
	in_token = 0;
	if (ft_count_quotes(line) % 2 != 0)
	{
		free_tokens(tokens);
		printf("Error: Unbalanced quotes detected\n");
		return (NULL);
	}
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]) && !in_token)
			i++;
		if (!line[i])
			break ;
		if (!process_token(line, &i, &tokens))
			return (NULL);
		in_token = 0;
	}
	return (tokens);
}

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}
