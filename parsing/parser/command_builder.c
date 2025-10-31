#include "../../include/parsing.h"

/*
 * Gère un token de redirection
 */

static int	process_redirection_token(t_token **current,
		t_redir_type redir_type, t_cmd *cmd)
{
	char	*target_file;
	t_redir	*new_redir;

	target_file = (*current)->value;
	new_redir = create_redir(redir_type, target_file);
	if (new_redir)
	{
		if (redir_type == R_HEREDOC)
			handle_heredoc(new_redir);
		if (new_redir)
			add_redir_back(&(cmd->redirs), new_redir);
		if (!new_redir)
			return (0);
		*current = (*current)->next;
	}
	return (1);
}

static int	build_redirection_token(t_token **current, t_cmd *cmd)
{
	t_redir_type	redir_type;

	if ((*current)->type == T_REDIR_IN)
		redir_type = R_IN;
	else if ((*current)->type == T_REDIR_OUT)
		redir_type = R_OUT_TRUNC;
	else if ((*current)->type == T_REDIR_APPEND)
		redir_type = R_OUT_APPEND;
	else if ((*current)->type == T_HEREDOC)
		redir_type = R_HEREDOC;
	else
		redir_type = R_IN;
	*current = (*current)->next;
	if (*current && (*current)->type == T_WORD)
	{
		process_redirection_token(current, redir_type, cmd);
	}
	return (1);
}

/*
 * Gère l'ajout d'un token WORD au tableau d'arguments
 */
static char	**init_args_array(const char *cmd_name, int *capacity)
{
	char	**args;

	*capacity = 10;
	args = malloc(sizeof(char *) * (*capacity));
	if (!args)
		return (NULL);
	if (cmd_name != NULL)
	{
		args[0] = ft_strdup(cmd_name);
		if (!args[0])
		{
			free(args);
			return (NULL);
		}
	}
	else
		args[0] = NULL;
	return (args);
}
/*
 * Trouve le premier T_WORD qui n'est pas après un opérateur de redirection
 * Retourne NULL si aucun nom de commande trouvé
 */
static char	*find_command_name(t_token *tokens)
{
	t_token	*current;
	int		after_redirection;

	if (!tokens)
		return (NULL);
	current = tokens;
	after_redirection = 0;
	while (current && current->type != T_PIPE && current->type != T_EOF)
	{
		if (current->type >= T_REDIR_IN && current->type <= T_HEREDOC)
		{
			after_redirection = 1;
		}
		else if (current->type == T_WORD)
		{
			if (!after_redirection)
				return (ft_strdup(current->value));
			after_redirection = 0;
		}
		current = current->next;
	}
	return (NULL);
}
/* Construit simultanément les arguments et redirections
* en parcourant les tokens une seule fois
Si c'est le nom de commande,
on le skip pour les args seulement si ce n'est pas le premier arg
Skip le nom de commande car il est déjà dans args[0]*/

static int	handle_word_token(char ***args, int *count, int *capacity,
		const char *value)
{
	char	**new_args;

	if (*count >= *capacity - 1)
	{
		*capacity *= 2;
		new_args = ft_realloc(*args, sizeof(char *) * (*capacity));
		if (!new_args)
			return (0);
		*args = new_args;
	}
	(*args)[*count] = ft_strdup(value);
	if (!(*args)[*count])
		return (0);
	(*count)++;
	return (1);
}

static int	handle_token(t_token **current, t_cmd *cmd, char ***args,
		int *arg_count, int *arg_capacity)
{
	if ((*current)->type == T_WORD)
	{
		if (cmd->name && *arg_count == 1 && strcmp((*current)->value,
				cmd->name) == 0)
			*current = (*current)->next;
		else
		{
			if (!handle_word_token(args, arg_count, arg_capacity,
					(*current)->value))
				return (0);
			*current = (*current)->next;
		}
	}
	else if ((*current)->type >= T_REDIR_IN && (*current)->type <= T_HEREDOC)
	{
		if (!build_redirection_token(current, cmd))
			return (0);
	}
	else
		*current = (*current)->next;
	return (1);
}

static int	process_tokens(t_token **tokens, t_cmd *cmd, char **args,
		int *arg_count)
{
	t_token	*current;
	int		arg_capacity;

	current = *tokens;
	arg_capacity = 10;
	while (current && current->type != T_PIPE && current->type != T_EOF)
	{
		if (!handle_token(&current, cmd, &args, arg_count, &arg_capacity))
		{
			free_args_on_error(args);
			return (0);
		}
	}
	*tokens = current;
	return (1);
}

static int	build_args_and_redirections(t_token **tokens, t_cmd *cmd)
{
	char	**args;
	int		arg_count;

	if (!tokens || !*tokens || !cmd)
		return (0);
	args = init_args_array(cmd->name, &arg_count);
	if (!args)
		return (0);
	arg_count = 1;
	if (!process_tokens(tokens, cmd, args, &arg_count))
		return (0);
	args[arg_count] = NULL;
	cmd->args = args;
	return (1);
}
/*
 * Construit une commande à partir des tokens
 Trouver le nom de la commande*/
t_cmd	*build_command(t_token **tokens)
{
	t_cmd	*cmd;
	t_token	*current;

	if (!tokens || !*tokens)
		return (NULL);
	cmd = create_cmd();
	printf("Created new command structure\n");
	if (!cmd)
		return (NULL);
	current = *tokens;
	cmd->name = find_command_name(current);
	if (!build_args_and_redirections(&current, cmd))
	{
		free_cmds(cmd);
		return (NULL);
	}
	*tokens = current;
	return (cmd);
}

/*
 * Crée une nouvelle structure de commande
 */
t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		return (NULL);
	}
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

/*
 * Libère le tableau d'arguments en cas d'erreur
 */
void	free_args_on_error(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
