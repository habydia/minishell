#include "parsing.h"

/*
 * Fonction principale du lexer
 * Transforme une ligne de commande en liste de tokens
 */
t_token	*line_lexer(const char *line)
{
	t_token	*tokens;

	if (!line || !*line)
		return (NULL);
	tokens = tokenize_line(line);
	if (!tokens)
		return (NULL);
	add_token_back(&tokens, create_token(T_EOF, NULL));
	return (tokens);
}
