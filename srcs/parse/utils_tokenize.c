#include "minishell.h"

int	count_pipes(char *input_str)
{
	int	count;

	count = 0;
	while (*input_str)
	{
		while (*input_str && check_char_whitespaces(*input_str))
			input_str++;
		if (check_char_is_quote(*input_str))
			input_str = skip_quoted_part(input_str);
		else if (*input_str == '|')
		{
			count++;
			input_str++;
		}
		else
			input_str++;
	}
	return (count);
}
