/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 05:00:52 by hadia             #+#    #+#             */
/*   Updated: 2025/11/15 01:04:31 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*line_lexer(const char *line)
{
	t_token	*tokens;

	if (!line || !*line)
		return (NULL);
	tokens = tokenize_line(line);
	if (!tokens)
		return (NULL);
	add_token_back(&tokens, create_token(T_EOF, NULL));
	return (tokens);
}

t_token	*expand_tokens(t_token *tokens, t_env *env, int *exit_status)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == T_WORD && current->value)
		{
			expanded = process_token_expansion(current->value, env,
					exit_status);
			if (expanded && expanded != current->value)
			{
				free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
	return (tokens);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;

	if (!tokens)
		return (NULL);
	cmds = handle_pipeline(tokens);
	return (cmds);
}

t_cmd	*parsing(const char *line, t_env *env, int *exit_status)
{
	t_token	*tokens;
	t_token	*token_start;
	t_cmd	*cmds;

	tokens = line_lexer(line);
	if (!tokens)
		return (NULL);
	token_start = tokens;
	if (syntax_errors(tokens))
	{
		free_tokens(token_start);
		return (NULL);
	}
	tokens = expand_tokens(tokens, env, exit_status);
	if (!tokens)
		return (NULL);
	cmds = parse_tokens(tokens);
	free_tokens(token_start);
	if (g_signal_status == SIG_HEREDOC_INTERRUPTED)
	{
		free_cmds(cmds);
		g_signal_status = SIG_NONE;
		*exit_status = 130;
		return (NULL);
	}
	return (cmds);
}
