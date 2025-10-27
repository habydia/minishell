#include "../../include/parsing.h"

static void	build_args_and_redirections(t_token **tokens, t_cmd *cmd);
static char	**init_args_array(const char *cmd_name, int *capacity);
static int	handle_word_token(char ***args, int *count, int *capacity,
				const char *value);
static void	handle_redirection_token(t_token **current, t_cmd *cmd);

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
	if (current && current->type == T_WORD)
	{
		cmd->name = ft_strdup(current->value);
		current = current->next;
	}
	build_args_and_redirections(&current, cmd);
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
 * Construit simultanément les arguments et redirections
 * en parcourant les tokens une seule fois
 */
static void	build_args_and_redirections(t_token **tokens, t_cmd *cmd)
{
	t_token	*current;
	char	**args;
	int		arg_count;
	int		arg_capacity;

	if (!tokens || !*tokens || !cmd)
		return ;
	current = *tokens;
	args = init_args_array(cmd->name, &arg_capacity);
	if (!args)
		return ;
	arg_count = 1;
	while (current && current->type != T_PIPE && current->type != T_EOF)
	{
		if (current->type == T_WORD)
		{
			if (!handle_word_token(&args, &arg_count, &arg_capacity,
					current->value))
			{
				free_args_on_error(args);
				return ;
			}
			current = current->next;
		}
		else if (current->type >= T_REDIR_IN && current->type <= T_HEREDOC)
		{
			handle_redirection_token(&current, cmd);
		}
		else
		{
			current = current->next;
		}
	}
	args[arg_count] = NULL;
	cmd->args = args;
	*tokens = current;
}

/*
 * Initialise le tableau d'arguments avec le nom de la commande
 */
static char	**init_args_array(const char *cmd_name, int *capacity)
{
	char	**args;

	*capacity = 10;
	args = malloc(sizeof(char *) * (*capacity));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(cmd_name);
	if (!args[0])
	{
		free(args);
		return (NULL);
	}
	return (args);
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
		new_args = realloc(*args, sizeof(char *) * (*capacity));
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

/*
 * Gère un token de redirection
 */
static void	handle_redirection_token(t_token **current, t_cmd *cmd)
{
	t_redir_type	redir_type;
	t_redir			*new_redir;

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
		new_redir = create_redir(redir_type, (*current)->value);
		if (new_redir)
			add_redir_back(&(cmd->redirs), new_redir);
		*current = (*current)->next;
	}
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
