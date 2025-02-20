#include "minishell.h"

int	check_char_is_quote(char  c)
{
	if (c == '"' ||  c == '\'')
		return (1);
	return (0);
}

int	check_char_is_dollar(char  c)
{
	if (c == '$')
		return (1);
	return (0);
}
