#include "minishell.h"

int	check_char_is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

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
	if (check_char_is_redirect(cmd_str[i]))
		return(REDIRECT);
	else if (check_char_whitespaces(cmd_str[i]))
		return (EMPTY);
	else
		return (CMD);
}

// t_redirect_type	get_redirect_type(char *cmd_str, int i)
// {
// 	if (cmd_str[i] == '<' && cmd_str[i + 1] == '<')
// 		return(RD_HEREDOC);
// 	else if (cmd_str[i] == '<')
// 		return (RD_IN);
// 	else if (cmd_str[i] == '>' && cmd_str[i + 1] == '>')
// 		return (RD_APPEND);
// 	else
// 		return (RD_OUT);
// }

char *ft_strndup(char *src, size_t n)
{
    size_t i;
    char *dest;

	if (!src)
		return (NULL);
	i = 0;
	dest = malloc(sizeof(size_t) * (n + 1));
    if (!dest)
        return (NULL);
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
