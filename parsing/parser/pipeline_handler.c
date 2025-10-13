#include "parsing.h"

/*
 * Fonction principale du parser
 * Transforme une liste de tokens en AST de commandes
 */
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;

	if (!tokens)
		return (NULL);
	cmds = handle_pipeline(tokens);
	return (cmds);
}

/*
 * Gère les pipelines - divise les tokens en commandes séparées par des pipes
 */
t_cmd	*handle_pipeline(t_token *tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;
	t_token	*current_token;

	if (!tokens)
		return (NULL);
	current_token = tokens;
	first_cmd = build_command(&current_token);
	if (!first_cmd)
		return (NULL);
	current_cmd = first_cmd;
	while (current_token && current_token->type != T_EOF)
	{
		if (current_token->type == T_PIPE)
		{
			current_token = current_token->next;
			new_cmd = build_command(&current_token);
			if (new_cmd)
			{
				current_cmd->next = new_cmd;
				current_cmd = new_cmd;
			}
		}
		else
			current_token = current_token->next;
	}
	return (first_cmd);
}
