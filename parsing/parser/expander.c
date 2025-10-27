#include "../../include/parsing.h"

static char	*process_token_expansion(const char *value);
static char	*remove_quotes(const char *value, char quote_type);
static char	*expand_simple_string(const char *str);

int			g_exit_status = 0;

/*
 * Fonction principale pour l'expansion des tokens
 * Parcourt tous les tokens et effectue l'expansion selon les règles
 */
t_token	*expand_tokens(t_token *tokens)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == T_WORD && current->value)
		{
			expanded = process_token_expansion(current->value);
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

/*
 * Traite l'expansion d'un token selon son type (guillemets ou non)
 */
static char	*process_token_expansion(const char *value)
{
	int		len;
	char	*temp;
	char	*expanded;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	if (len < 2)
		return (expand_simple_string(value));
	if (value[0] == '\'' && value[len - 1] == '\'')
	{
		return (remove_quotes(value, '\''));
	}
	else if (value[0] == '"' && value[len - 1] == '"')
	{
		temp = remove_quotes(value, '"');
		expanded = expand_simple_string(temp);
		free(temp);
		return (expanded);
	}
	else
	{
		return (expand_simple_string(value));
	}
}

/*
 * Supprime les guillemets d'ouverture et de fermeture
 */
static char	*remove_quotes(const char *value, char quote_type)
{
	int		len;
	char	*result;
	int		i;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	if (len < 2 || value[0] != quote_type || value[len - 1] != quote_type)
		return (ft_strdup(value));
	result = malloc(len - 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len - 2)
	{
		result[i] = value[i + 1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
 * Effectue l'expansion des variables dans une chaîne simple
 */
static char	*expand_simple_string(const char *str)
{
	char			*result;
	size_t			result_size;
	size_t			i;
	size_t			j;
	t_expand_data	data;

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
	{
		handle_expansion(str, &i, &j, &data);
	}
	result[j] = '\0';
	return (result);
}

static void	handle_expansion(const char *str, size_t *i, size_t *j,
		t_expand_data *data)
{
	char	*new_result;

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
			return ;
		}
	}
	else
	{
		if (*j >= *(data->result_size) - 1)
		{
			*(data->result_size) *= 2;
			new_result = realloc(*data->result, *(data->result_size));
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
