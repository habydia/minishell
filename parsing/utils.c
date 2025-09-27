#include "../include/parsing.h"

/* ========== LIBÉRATION MÉMOIRE ========== */

/*
 * Libère une liste de tokens
 */
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

/*
 * Libère une liste de commandes
 */
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->args)
			free_args(current->args);
		if (current->redirs)
			free_redirs(current->redirs);
		free(current);
		current = next;
	}
}

/*
 * Libère une liste de redirections
 */
void	free_redirs(t_redir *redirs)
{
	t_redir	*current;
	t_redir	*next;

	current = redirs;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

/*
 * Libère un tableau d'arguments
 */
void	free_args(char **args)
{
	int	i;

	if (!args)
		return;
	
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/* ========== FONCTIONS DE DEBUG ========== */

/*
 * Affiche la liste de tokens (pour debug)
 */
void	print_tokens(t_token *tokens)
{
	t_token	*current;
	char	*type_names[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", 
						 "REDIR_APPEND", "HEREDOC", "EOF"};

	current = tokens;
	printf("=== TOKENS ===\n");
	while (current)
	{
		printf("[%s]: '%s'\n", type_names[current->type], 
			   current->value ? current->value : "NULL");
		current = current->next;
	}
	printf("==============\n");
}
