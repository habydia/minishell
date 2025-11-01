#include "../../include/parsing.h"
//ok nb ligne
//nb func 3

void	free_redirs(t_redir *redirs)
{
	t_redir	*current;
	t_redir	*temp;

	current = redirs;
	while (current)
	{
		temp = current->next;
		free(current->file);
		free(current);
		current = temp;
	}
}

static void	build_pipeline(t_token **current_token, t_cmd **current_cmd)
{
	t_cmd	*new_cmd;

	while (current_token && *current_token && (*current_token)->type != T_EOF)
	{
		if ((*current_token)->type == T_PIPE)
		{
			*current_token = (*current_token)->next;
			new_cmd = build_command(current_token);
			if (new_cmd)
			{
				(*current_cmd)->next = new_cmd;
				*current_cmd = new_cmd;
			}
		}
		else
			*current_token = (*current_token)->next;
	}
}
t_cmd	*handle_pipeline(t_token *tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*current_cmd;
	t_token	*current_token;

	// t_cmd	*new_cmd;
	if (!tokens)
		return (NULL);
	current_token = tokens;
	first_cmd = build_command(&current_token);
	if (!first_cmd)
		return (NULL);
	current_cmd = first_cmd;
	build_pipeline(&current_token, &current_cmd);
	return (first_cmd);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;

	if (!tokens)
		return (NULL);
	cmds = handle_pipeline(tokens);
	return (cmds);
}