#include "../../include/parsing.h"

/*
 * Construit une commande à partir des tokens
 */
t_cmd	*build_command(t_token **tokens)
{
	t_cmd	*cmd;
	t_token	*current;

	if (!tokens || !*tokens)
		return (NULL);
	
	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	
	current = *tokens;
	
	// Le premier token doit être le nom de la commande
	if (current && current->type == T_WORD)
	{
		cmd->name = ft_strdup(current->value);
		current = current->next;
	}
	
	// Construire les arguments et redirections
	cmd->args = build_args_array(&current);
	cmd->redirs = parse_redirections(&current);
	
	*tokens = current; // Mettre à jour le pointeur
	return (cmd);
}

/*
 * Construit le tableau d'arguments
 */
char	**build_args_array(t_token **tokens)
{
	t_token	*current;
	char	**args;
	int		count;
	int		i;

	if (!tokens || !*tokens)
		return (NULL);
	
	// Compter les arguments
	current = *tokens;
	count = 0;
	while (current && current->type != T_PIPE && current->type != T_EOF)
	{
		if (current->type == T_WORD)
			count++;
		else if (current->type >= T_REDIR_IN && current->type <= T_HEREDOC)
		{
			// Ignorer le token de redirection et son fichier
			current = current->next;
			if (current && current->type == T_WORD)
				current = current->next;
			continue;
		}
		current = current->next;
	}
	
	// Allouer le tableau d'arguments (+1 pour le nom de la commande, +1 pour NULL)
	args = malloc(sizeof(char *) * (count + 2));
	if (!args)
		return (NULL);
	
	// Remplir le tableau
	current = *tokens;
	i = 0;
	
	// Ajouter le nom de la commande en premier
	if (current && current->type == T_WORD)
	{
		args[i++] = ft_strdup(current->value);
		current = current->next;
	}
	
	// Ajouter les autres arguments
	while (current && current->type != T_PIPE && current->type != T_EOF && i < count + 1)
	{
		if (current->type == T_WORD)
		{
			args[i++] = ft_strdup(current->value);
			current = current->next;
		}
		else if (current->type >= T_REDIR_IN && current->type <= T_HEREDOC)
		{
			// Ignorer les redirections
			current = current->next;
			if (current && current->type == T_WORD)
				current = current->next;
		}
		else
			current = current->next;
	}
	
	args[i] = NULL;
	*tokens = current;
	
	return (args);
}

/*
 * Crée une nouvelle structure de commande
 */
t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	
	return (cmd);
}
