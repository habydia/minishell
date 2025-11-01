#include "../../include/parsing.h"
//ln ligne ok
//nb func5
int	tokenize_operator(const char *line, int *i, int *start,
		t_token **tokens)
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
	add_token_back(tokens, create_token(type, value));
	free(value);
	return (1);
}

int	tokenize_quote(const char *line, int *start, int *i,
		t_token **tokens)
{
	char	*quoted_value;
	int		j;

	quoted_value = malloc(*i - *start + 1);
	if (!quoted_value)
	{
		free_tokens(*tokens);
		return (0);
	}
	if (quoted_value)
	{
		j = 0;
		while (j < *i - *start)
		{
			quoted_value[j] = line[*start + j];
			j++;
		}
		quoted_value[j] = '\0';
		add_token_back(tokens, create_token(T_WORD, quoted_value));
		free(quoted_value);
	}
	return (1);
}

int	tokenize_word(int *start, int *i, t_token **tokens,
		const char *line)
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
	add_token_back(tokens, create_token(T_WORD, word));
	free(word);
	return (1);
}
/*
 * Découpe une ligne en tokens
 */

int	handle_quote(const char *line, int *i, int *start, t_token **tokens)
{
	char	quote_type;

	quote_type = line[*i];
	(*i)++;          // passer le guillemet d'ouverture
	*start = *i - 1; // inclure le guillemet d'ouverture
	while (line[*i] && line[*i] != quote_type)
		(*i)++;
	if (line[*i] == quote_type)
		(*i)++; // inclure le guillemet de fermeture
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