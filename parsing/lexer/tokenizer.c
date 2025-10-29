#include "../../include/parsing.h"

static void	tokenize_operator(const char *line, int *i, int *start,
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
		return ;
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
}

static void	tokenize_quote(const char *line, int *start, int *i,
		t_token **tokens)
{
	char	*quoted_value;
	int		j;

	quoted_value = malloc(*i - *start + 1);
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
}

static void	tokenize_word(int *start, int *i, t_token **tokens,
		const char *line)
{
	char	*word;
	int		j;

	word = malloc(*i - *start + 1);
	if (!word)
	{
		free_tokens(*tokens);
		return ;
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
}
/*
 * Découpe une ligne en tokens
 */

static void	handle_quote(const char *line, int *i, int *start, t_token **tokens)
{
	char	quote_type;

	quote_type = line[*i];
	i++;           // passer le guillemet d'ouverture
	start = i - 1; // inclure le guillemet d'ouverture
	while (line[*i] && line[*i] != quote_type)
		i++;
	if (line[*i] == quote_type)
		i++; // inclure le guillemet de fermeture
	tokenize_quote(line, start, i, tokens);
}

t_token	*tokenize_line(const char *line)
{
	t_token	*tokens;
	int		i;
	int		start;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		start = i;
		if (is_operator_char(line[i]))
			tokenize_operator(line, &i, &start, &tokens);
		else if (line[i] == '"' || line[i] == '\'')
			handle_quote(line, &i, &start, &tokens);
		else
		{
			while (line[i] && !ft_isspace(line[i])
				&& !is_operator_char(line[i]))
				i++;
			tokenize_word(&start, &i, &tokens, line);
		}
	}
	return (tokens);
}

/*
 * Crée un nouveau token
 */
t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value ? ft_strdup(value) : NULL;
	token->next = NULL;
	return (token);
}

/*
 * Ajoute un token à la fin de la liste
 */
void	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
