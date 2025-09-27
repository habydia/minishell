#include "../../include/parsing.h"

/*
 * Parse les redirections à partir des tokens
 */
t_redir	*parse_redirections(t_token **tokens)
{
	t_redir	*redirs;
	t_redir	*new_redir;
	t_token	*current;
	t_redir_type redir_type;

	if (!tokens || !*tokens)
		return (NULL);
	
	redirs = NULL;
	current = *tokens;
	
	while (current && current->type != T_PIPE && current->type != T_EOF)
	{
		// Vérifier si c'est une redirection
		if (current->type >= T_REDIR_IN && current->type <= T_HEREDOC)
		{
			// Déterminer le type de redirection
			switch (current->type)
			{
				case T_REDIR_IN:
					redir_type = R_IN;
					break;
				case T_REDIR_OUT:
					redir_type = R_OUT_TRUNC;
					break;
				case T_REDIR_APPEND:
					redir_type = R_OUT_APPEND;
					break;
				case T_HEREDOC:
					redir_type = R_HEREDOC;
					break;
				default:
					redir_type = R_IN;
			}
			
			// Passer au token suivant (le fichier)
			current = current->next;
			if (current && current->type == T_WORD)
			{
				new_redir = create_redir(redir_type, current->value);
				if (new_redir)
					add_redir_back(&redirs, new_redir);
				current = current->next;
			}
		}
		else if (current->type == T_WORD)
		{
			// Ce mot fait partie des arguments, pas des redirections
			current = current->next;
		}
		else
		{
			current = current->next;
		}
	}
	
	*tokens = current;
	return (redirs);
}

/*
 * Crée une nouvelle redirection
 */
t_redir	*create_redir(t_redir_type type, const char *file)
{
	t_redir	*redir;

	if (!file)
		return (NULL);
	
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = NULL;
	
	return (redir);
}

/*
 * Ajoute une redirection à la fin de la liste
 */
void	add_redir_back(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*current;

	if (!redirs || !new_redir)
		return;
	
	if (!*redirs)
	{
		*redirs = new_redir;
		return;
	}
	
	current = *redirs;
	while (current->next)
		current = current->next;
	
	current->next = new_redir;
}
