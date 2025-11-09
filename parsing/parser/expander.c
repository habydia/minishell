/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 04:59:50 by hadia             #+#    #+#             */
/*   Updated: 2025/11/09 01:48:46 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_expansion(const char *str, size_t *i, size_t *j,
		t_expand_data *data)
{
	if (str[*i] == '\\' && str[*i + 1] == '$')
	{
		(*data->result)[(*j)++] = '$';
		(*i) += 2;
	}
	else if (str[*i] == '$')
	{
		if (!handle_dollar_sign(str, i, data))
		{
			free(*data->result);
			*data->result = NULL;
			return (0);
		}
	}
	return (1);
}

static void	handle_mixed_quotes(const char *str, size_t *i)
{
	if ((str[*i] == '"' && str[*i + 1] == '"') || (str[*i] == '\'' && str[*i
			+ 1] == '\''))
	{
		(*i) += 2;
		return ;
	}
	if (str[*i] == '"' || str[*i] == '\'')
	{
		(*i)++;
		return ;
	}
}

static void	handle_expansion(const char *str, size_t *i, size_t *j,
		t_expand_data *data)
{
	char	*new_result;

	handle_mixed_quotes(str, i);
	if (!process_expansion(str, i, j, data))
		return ;
	if (str[*i])
	{
		if (*j >= *(data->result_size) - 1)
		{
			*(data->result_size) *= 2;
			new_result = ft_realloc(*data->result, *j, *(data->result_size));
			if (!new_result)
			{
				free(*data->result);
				*data->result = NULL;
				return ;
			}
			*data->result = new_result;
		}
		(*data->result)[(*j)++] = str[(*i)++];
	}
}

static char	*expand_simple_string(const char *str, t_env *env)
{
	char			*result;
	size_t			result_size;
	size_t			i;
	size_t			j;
	t_expand_data	data;

	data.env = env;
	if (!str)
		return (NULL);
	result_size = ft_strlen(str) * 2 + 1;
	result = malloc(result_size);
	if (!result)
		return (NULL);
	data.result = &result;
	data.result_size = &result_size;
	data.j = &j;
	i = 0;
	j = 0;
	while (str[i])
		handle_expansion(str, &i, &j, &data);
	result[j] = '\0';
	return (result);
}

char	*process_token_expansion(const char *value, t_env *env)
{
	int		len;
	char	*temp;
	char	*expanded;
	int		i;

	i = 0;
	if (!value)
		return (NULL);
	len = ft_strlen(value);
	if (len < 2)
		return (expand_simple_string(value, env));
	if (value[0] == '\'' && value[len - 1] == '\'')
		return (remove_quotes(value, '\''));
	else if (value[0] == '"' && value[len - 1] == '"')
	{
		temp = remove_quotes(value, '"');
		expanded = expand_simple_string(temp, env);
		free(temp);
		return (expanded);
	}
	else
		return (expand_simple_string(value, env));
}
