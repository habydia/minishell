/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 04:59:58 by hadia             #+#    #+#             */
/*   Updated: 2025/11/01 05:17:03 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

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
