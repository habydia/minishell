/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 04:59:50 by hadia             #+#    #+#             */
/*   Updated: 2025/11/19 01:13:02 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_expansion(const char *str, size_t *i, t_expand_data *data)
{
	size_t	old_i;

	old_i = *i;
	handle_quote_context(str, i, data);
	if (str[*i] == '\0' || *i != old_i)
		return (1);
	if (str[*i] == '$' && (!data->in_quote || data->quote_type == '"'))
	{
		if (!handle_dollar_sign(str, i, data))
			return (0);
	}
	else
	{
		if (!handle_realloc(data))
			return (0);
		data->result[data->j++] = str[(*i)++];
	}
	return (1);
}

static int	perform_expansion(const char *str, t_expand_data *data)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!handle_expansion(str, &i, data))
			return (0);
	}
	return (1);
}

static char	*expand_simple_string(const char *str, t_env *env, int in_dquotes,
		int *exit_status)
{
	t_expand_data	data;

	if (!str)
		return (NULL);
	data.env = env;
	data.exit_status = exit_status;
	data.in_quote = in_dquotes;
	data.quote_type = (in_dquotes * '"');
	data.result_size = ft_strlen(str) * 2 + 1;
	data.result = malloc(data.result_size);
	if (!data.result)
		return (NULL);
	data.j = 0;
	if (!perform_expansion(str, &data))
	{
		free(data.result);
		return (NULL);
	}
	data.result[data.j] = '\0';
	return (data.result);
}

char	*process_token_expansion(const char *value, t_env *env,
		int *exit_status)
{
	int		len;
	char	*temp;
	char	*expanded;
	char	*result;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	if (len >= 2 && value[0] == '\'' && value[len - 1] == '\'')
	{
		result = remove_quotes(value, '\'');
		return (result);
	}
	if (len >= 2 && value[0] == '"' && value[len - 1] == '"')
	{
		temp = remove_quotes(value, '"');
		expanded = expand_simple_string(temp, env, 1, exit_status);
		free(temp);
		return (expanded);
	}
	result = expand_simple_string(value, env, 0, exit_status);
	return (result);
}
