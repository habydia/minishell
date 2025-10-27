#include "../../include/parsing.h"

/*
 * Détermine le type d'opérateur et avance l'index
 */
t_token_type	get_operator_type(const char *str, int *i)
{
	if (str[*i] == '|')
	{
		(*i)++;
		return (T_PIPE);
	}
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			(*i) += 2;
			return (T_HEREDOC);
		}
		else
		{
			(*i)++;
			return (T_REDIR_IN);
		}
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			(*i) += 2;
			return (T_REDIR_APPEND);
		}
		else
		{
			(*i)++;
			return (T_REDIR_OUT);
		}
	}
	(*i)++;
	return (T_WORD);
}

/*
 * Vérifie si un caractère est le début d'un opérateur
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
