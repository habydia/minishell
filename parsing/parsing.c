/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 05:00:52 by hadia             #+#    #+#             */
/*   Updated: 2025/11/01 05:21:52 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*parsing(const char *line)
{
	t_token	*tokens;
	t_token	*token_start;
	t_cmd	*cmds;

	tokens = line_lexer(line);
	if (!tokens)
		return (NULL);
	token_start = tokens;
	tokens = expand_tokens(tokens);
	if (!tokens)
		return (NULL);
	cmds = parse_tokens(tokens);
	free_tokens(token_start);
	return (cmds);
}
