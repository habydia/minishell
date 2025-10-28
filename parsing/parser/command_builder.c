#include "../../include/parsing.h"

/*
 * Gère un token de redirection
 */
static int	handle_redirection_token(t_token **current, t_cmd *cmd)
{
	t_redir_type	redir_type;
	t_redir			*new_redir;
	char			*target_file;

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
	}
	return (1);
}

/*
 * Gère l'ajout d'un token WORD au tableau d'arguments
 */
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
	{
		free(*args);
		return (0);
	}
	(*count)++;
	return (1);
}
static char	**init_args_array(const char *cmd_name, int *capacity)
{
	char	**args;

	*capacity = 10;
	args = malloc(sizeof(char *) * (*capacity));
	if (!args)
		return (NULL);
	if (args[0] == NULL) // si pas de 1er commande nom de cmd vide
		args[0] = ft_strdup(cmd_name);
	if (!args[0])
	{
		free(args);
		return (NULL);
	}
	return (args);
}
//  * Construit simultanément les arguments et redirections
//  * en parcourant les tokens une seule fois
//  */
static int	build_args_and_redirections(t_token **tokens, t_cmd *cmd)
{
	t_token	*current;
	char	**args;
	int		arg_count;
	int		arg_capacity;

	if (!tokens || !*tokens || !cmd)
		return (0);
	current = *tokens;
	args = init_args_array(cmd->name, &arg_capacity);
	if (!args)
		return (0);
	arg_count = 1;
	while (current && current->type != T_PIPE && current->type != T_EOF)
	{
		if (current->type == T_WORD)
		{
			if (!handle_word_token(&args, &arg_count, &arg_capacity,
					current->value))
			{
				free_args_on_error(args);
				return (0);
			}
			current = current->next;
		}
		else if (current->type >= T_REDIR_IN && current->type <= T_HEREDOC)
		{
			if (!handle_redirection_token(&current, cmd))
			{
				free_args_on_error(args);
				return (0);
			}
		}
		else
		{
			current = current->next;
		}
	}
	args[arg_count] = NULL;
	cmd->args = args;
	*tokens = current;
	return (1);
}
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
	printf("Created new command structure\n");
	if (!cmd)
		return (NULL);
	current = *tokens;
	if (current && current->type == T_WORD)
	{
		cmd->name = ft_strdup(current->value);
		if (!cmd->name)
		{
			free_cmds(cmd);
			return (NULL);
		}
		current = current->next;
	}
	else
	{
		// Pas de nom de commande - créer une commande vide
		cmd->name = NULL;
	}
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
