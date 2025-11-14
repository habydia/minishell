/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 01:42:33 by hadia             #+#    #+#             */
/*   Updated: 2025/11/14 19:20:48 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_single_quote(bool *in_single, bool in_double, int *count)
{
	if (in_double == false)
	{
		if (*in_single == false)
			*in_single = true;
		else
			*in_single = false;
		(*count)++;
	}
}

static void	handle_double_quote(bool *in_double, bool in_single, int *count)
{
	if (in_single == false)
	{
		if (*in_double == false)
			*in_double = true;
		else
			*in_double = false;
		(*count)++;
	}
}

int	ft_count_quotes(const char *str)
{
	int		i;
	int		single_quotes;
	int		double_quotes;
	bool	in_single;
	bool	in_double;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	in_single = false;
	in_double = false;
	while (str[i])
	{
		if (str[i] == '\'')
			handle_single_quote(&in_single, in_double, &single_quotes);
		else if (str[i] == '"')
			handle_double_quote(&in_double, in_single, &double_quotes);
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (1);
	return (0);
}

int	is_quote_balanced(const char *line, int start, int end)
{
	char	*substr;
	int		result;

	substr = ft_substr(line, start, end - start);
	if (!substr)
		return (0);
	result = !ft_count_quotes(substr);
	free(substr);
	return (result);
}

int	find_closing_quote(const char *line, int *i, char quote_type)
{
	int	temp;

	(*i)++;
	while (line[*i])
	{
		if (line[*i] == quote_type)
			return (1);
		else if ((quote_type == '"' && line[*i] == '\'') || (quote_type != '"'
				&& line[*i] == '"'))
		{
			temp = *i;
			(*i)++;
			while (line[*i] && line[*i] != line[temp])
				(*i)++;
			if (line[*i])
				(*i)++;
		}
		(*i)++;
	}
	return (0);
}
