#include "../include/parsing.h"

// ok nb ligne
// ok nb function 4

t_cmd	*parsing(const char *line)
{
	t_token *tokens;
	t_token *token_start;
	t_cmd *cmds;

	tokens = line_lexer(line);
	if (!tokens)
		return (NULL);

	token_start = tokens;
	tokens = expand_tokens(tokens);
	if (!tokens)
		return (NULL);

	cmds = parse_tokens(tokens);

	free_tokens(token_start);
	return (cmds);
}