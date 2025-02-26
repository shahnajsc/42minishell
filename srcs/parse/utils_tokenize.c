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

t_token_type	get_token_type(char *cmd_str, int i)
{
	if (cmd_str[i] == '<' && cmd_str[i + 1] == '<')
		return(RD_HEREDOC);
	else if (cmd_str[i] == '<')
		return (RD_IN);
	else if (cmd_str[i] == '>' && cmd_str[i + 1] == '>')
		return (RD_APPEND);
	else if (cmd_str[i] == '>')
		return (RD_OUT);
	else
		return (CMD);
}
