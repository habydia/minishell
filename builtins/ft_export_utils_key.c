/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:30:25 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/09 16:38:08 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "minishell.h"

void	handle_key_value(const char *str, char *eq_pos, char **key_out,
		char **value_out)
{
	*key_out = ft_strndup(str, eq_pos - str);
	if (!*key_out)
	{
		perror("malloc");
		*value_out = NULL;
		return ;
	}
	*value_out = ft_strdup(eq_pos + 1);
	if (!*value_out)
	{
		perror("malloc");
		free(*key_out);
		*key_out = NULL;
	}
}

void	handle_key_only(const char *str, char **key_out, char **value_out)
{
	*key_out = ft_strdup(str);
	if (!*key_out)
		perror("malloc");
	*value_out = NULL;
}

void	split_key_value(const char *str, char **key_out, char **value_out)
{
	char	*eq_pos;

	eq_pos = ft_strchr(str, '=');
	if (eq_pos)
		handle_key_value(str, eq_pos, key_out, value_out);
	else
		handle_key_only(str, key_out, value_out);
}
