
#include "../../include/parsing.h"
//nb ligne ok
//nb func 5
int	handle_word_token(char ***args, int *count, int *capacity,
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



int	handle_token(t_token **current, t_cmd *cmd, char ***args,
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

    int	process_tokens(t_token **tokens, t_cmd *cmd, char **args,
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

    /*
 * Gère l'ajout d'un token WORD au tableau d'arguments
 */
char	**init_args_array(const char *cmd_name, int *capacity)
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