#include "../../include/parsing.h"

/*
 * Découpe une ligne en tokens
 */
t_token	*tokenize_line(const char *line)
{
	t_token	*tokens;
	int		i;
	int		start;

	tokens = NULL;
	i = 0;
	
	while (line[i])
	{
		// Ignorer les espaces
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
			
		start = i;
		
		// Vérifier si c'est un opérateur
		if (is_operator_char(line[i]))
		{
			t_token_type type = get_operator_type(line, &i);
			char *value = malloc(i - start + 1);
			if (value)
			{
				int j = 0;
				while (j < i - start)
				{
					value[j] = line[start + j];
					j++;
				}
				value[j] = '\0';
				add_token_back(&tokens, create_token(type, value));
				free(value);
			}
		}
		// Vérifier si c'est une section quotée
		else if (line[i] == '"' || line[i] == '\'')
		{
			char *quoted_value = handle_quotes(line, &i);
			if (quoted_value)
			{
				add_token_back(&tokens, create_token(T_WORD, quoted_value));
				free(quoted_value);
			}
		}
		// Mot normal
		else
		{
			while (line[i] && !ft_isspace(line[i]) && !is_operator_char(line[i]))
				i++;
			char *word = malloc(i - start + 1);
			if (word)
			{
				int j = 0;
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
		return;
	
	if (!*tokens)
	{
		*tokens = new_token;
		return;
	}
	
	current = *tokens;
	while (current->next)
		current = current->next;
	
	current->next = new_token;
}