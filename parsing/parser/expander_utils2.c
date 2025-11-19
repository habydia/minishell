/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:58:33 by hadia             #+#    #+#             */
/*   Updated: 2025/11/19 01:15:53 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_context(const char *str, size_t *i, t_expand_data *data)
{
	char	current_quote;

	current_quote = str[*i];
	if (current_quote == '\'' || current_quote == '"')
	{
		if (!data->in_quote)
		{
			data->in_quote = 1;
			data->quote_type = current_quote;
			(*i)++;
			return ;
		}
		if (data->quote_type == current_quote)
		{
			data->in_quote = 0;
			data->quote_type = 0;
			(*i)++;
			return ;
		}
	}
}

int	handle_realloc(t_expand_data *data)
{
	char	*new_result;

	if (data->j >= data->result_size - 1)
	{
		data->result_size *= 2;
		new_result = ft_realloc(data->result, data->j, data->result_size);
		if (!new_result)
			return (0);
		data->result = new_result;
	}
	return (1);
}
