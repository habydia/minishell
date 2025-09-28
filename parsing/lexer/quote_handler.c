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
	(*i)++;
	start = *i;
	

	while (str[*i] && str[*i] != quote_type)
		(*i)++;
	
	if (!str[*i])
		return (NULL);
	
	len = *i - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	

	int j = 0;
	while (j < len)
	{
		result[j] = str[start + j];
		j++;
	}
	result[j] = '\0';
	
	(*i)++;
	
	return (result);
}
