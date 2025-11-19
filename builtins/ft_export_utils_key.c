/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:30:25 by lebroue           #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_key_and_value(const char *str, char *equal_position,
		char **key_out, char **value_out)
{
	*key_out = ft_strndup(str, equal_position - str);
	if (!*key_out)
	{
		perror("malloc");
		*value_out = NULL;
		return ;
	}
	*value_out = ft_strdup(equal_position + 1);
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

void	split_variable_key_and_value(const char *str, char **key_out,
		char **value_out)
{
	char	*equal_position;

	equal_position = ft_strchr(str, '=');
	if (equal_position)
		handle_key_and_value(str, equal_position, key_out, value_out);
	else
		handle_key_only(str, key_out, value_out);
}
