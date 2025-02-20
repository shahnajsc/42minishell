#include "minishell.h"



char	*expansion_input(t_mshell *mshell, char *input_str)
{
	while (*input_str)
	{
		if (check_char_is_quote(*input_str))
			;//expand quote;
		else if (check_char_is_dollar(*input_str))
			;//expand dllar (VAR and Exit value);
		else
			input_str++;
	}
	return (input_str);
}
