#include "../../include/parsing.h"

/*
 * Gère les sections quotées (simple et double guillemets)
 * Retourne le contenu sans les guillemets
 */
char	*handle_quotes(const char *str, int *i)
{
	char	quote_type;
	int		start;
	int		len;
	char	*result;

	quote_type = str[*i];
	(*i)++; // Passer le guillemet d'ouverture
	start = *i;
	
	// Chercher le guillemet de fermeture
	while (str[*i] && str[*i] != quote_type)
		(*i)++;
	
	if (!str[*i]) // Guillemet non fermé
		return (NULL);
	
	len = *i - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	
	// Copier le contenu entre guillemets
	int j = 0;
	while (j < len)
	{
		result[j] = str[start + j];
		j++;
	}
	result[j] = '\0';
	
	(*i)++; // Passer le guillemet de fermeture
	
	return (result);
}

/*
 * Vérifie si une position donnée est dans une section quotée
 */
int	is_quoted_section(const char *str, int start)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	
	while (i < start && str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	
	return (in_single_quote || in_double_quote);
}
