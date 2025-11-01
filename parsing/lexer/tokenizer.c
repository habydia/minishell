#include "../../include/parsing.h"

// ok nb ligne
//nb funct 4


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
		if (is_operator_char(line[i]) || line[i] == '"' || line[i] == '\'')
		{
			if (!handle_operator_and_quote(&i, &start, line, &tokens))
				return (0);
		}
		else
		{
			while (line[i] && !ft_isspace(line[i])
				&& !is_operator_char(line[i]))
				i++;
			if (!tokenize_word(&start, &i, &tokens, line))
				return (0);
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
