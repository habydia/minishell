#include "parsing.h"

/*
 * Découpe une ligne en tokens
 */
t_token	*tokenize_line(const char *line)
{
	t_token			*tokens;
	int				i;
	int				start;
	t_token_type	type;
	char			*value;
	char			quote_type;
	char			*quoted_value;
	int				j;
	char			*word;

	// int				j;
	// int				j;
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
		{
			type = get_operator_type(line, &i);
			value = malloc(i - start + 1);
			if (!value)
			{
				free_tokens(tokens);
				return (NULL);
			}
			j = 0;
			while (j < i - start)
			{
				value[j] = line[start + j];
				j++;
			}
			value[j] = '\0';
			add_token_back(&tokens, create_token(type, value));
			free(value);
		}
		else if (line[i] == '"' || line[i] == '\'')
		{
			quote_type = line[i];
			i++;           // passer le guillemet d'ouverture
			start = i - 1; // inclure le guillemet d'ouverture
			// trouver le guillemet de fermeture
			while (line[i] && line[i] != quote_type)
				i++;
			if (line[i] == quote_type)
				i++; // inclure le guillemet de fermeture
			// créer le token avec les guillemets inclus
			quoted_value = malloc(i - start + 1);
			if (quoted_value)
			{
				j = 0;
				while (j < i - start)
				{
					quoted_value[j] = line[start + j];
					j++;
				}
				quoted_value[j] = '\0';
				add_token_back(&tokens, create_token(T_WORD, quoted_value));
				free(quoted_value);
			}
		}
		else
		{
			while (line[i] && !ft_isspace(line[i])
				&& !is_operator_char(line[i]))
				i++;
			word = malloc(i - start + 1);
			if (!word)
			{
				free_tokens(tokens);
				return (NULL);
			}
			j = 0;
			while (j < i - start)
			{
				word[j] = line[start + j];
				j++;
			}
			word[j] = '\0';
			add_token_back(&tokens, create_token(T_WORD, word));
			free(word);
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
	t_token *current;

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