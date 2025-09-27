#include "../../include/parsing.h"

/*
 * Fonction principale du lexer
 * Transforme une ligne de commande en liste de tokens
 */
t_token	*line_lexer(const char *line)
{
	t_token	*tokens;

	if (!line || !*line)
		return (NULL);
	
	// Tokenisation de la ligne
	tokens = tokenize_line(line);
	if (!tokens)
		return (NULL);
	
	// Ajouter un token EOF à la fin
	add_token_back(&tokens, create_token(T_EOF, NULL));
	
	return (tokens);
}
