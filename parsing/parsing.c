#include "../include/parsing.h"

// ok nb ligne

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		temp = current->next;
		free(current->name);
		free_args_on_error(current->args);
		free_redirs(current->redirs);
		free(current);
		current = temp;
	}
}

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

t_cmd	*parsing(const char *line)
{
	t_token *tokens;
	t_cmd *cmds;

	tokens = line_lexer(line);
	if (!tokens)
		return (NULL);

	tokens = expand_tokens(tokens);
	if (!tokens)
		return (NULL);

	cmds = parse_tokens(tokens);
	if (!cmds)
		free_cmds(cmds);

	free_tokens(tokens);
	return (cmds);
}