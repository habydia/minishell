#include "../../include/parsing.h"

/*
 * Fonction principale du parser
 * Transforme une liste de tokens en AST de commandes
 */
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;

	if (!tokens)
		return (NULL);
	
	// Gestion des pipelines - construit la liste de commandes
	cmds = handle_pipeline(tokens);
	
	return (cmds);
}
