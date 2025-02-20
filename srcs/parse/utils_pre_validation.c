#include "minishell.h"

int	check_char_whitespaces(char c)
{
	if (c != 32 && (c < 9 || c > 13))
		return (0);
	return (1);
}

char	*skip_quoted_part(char *input_str)
{
	char	quote;

	quote = *input_str;
	input_str++;
	while (*input_str && *input_str != quote)
		input_str++;
	if (*input_str)
		input_str++;
	return (input_str);
}

char	*skip_unquoted_part(char *input_str)
{
	while (*input_str && (*input_str != '\'' && *input_str != '"' && *input_str != '|'))
		input_str++;
	return (input_str);
}

int	check_str_whitespaces(char *input_str)
{
	while (*input_str != '\0')
	{
		if (*input_str != 32 && (*input_str < 9 || *input_str > 13))
			return (0);
		input_str++;
	}
	return (1);
}
