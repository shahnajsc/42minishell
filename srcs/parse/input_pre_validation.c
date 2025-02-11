#include "minishell.h"

int	check_str_whitespaces(char *str);

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
	input_str++;
	return (input_str);
}

char	*skip_unquoted_part(char *input_str)
{
	while (*input_str && (*input_str != '\'' && *input_str != '"' && *input_str != '|'))
		input_str++;
	return (input_str);
}

int	check_backslash(char *input_str)
{
	while (*input_str != '\0')
	{
		if (*input_str && (*input_str == '\'' || *input_str == '"'))
			input_str = skip_quoted_part(input_str);
		else if (*input_str && *input_str == '\\')
			return (1);
		else
			input_str++;
	}
	return (0);
}

int	check_invalid_redirection(char *input_str)                                                                                                                                                 
{
	int	rd_in;
	int	rd_out;

	rd_in = 0;
	rd_out = 0;
	while (*input_str != '\0')
	{
		if (*input_str == '<')
		{
			while (*input_str && *input_str == '<')
			{
				rd_in++;
				input_str++;
			}
			if (rd_in > 2)
				return (1);
		}
		else if (*input_str == '>')
		{
			while (*input_str && *input_str == '<')
			{
				rd_out++;
				input_str++;
			}
			if (rd_out > 2)
				return (1);
		}
		else
			input_str++;
	}
	return (0);
}

int	check_invalid_pipe(char *input_str)
{
	while (check_char_whitespaces(*input_str))
		input_str++;
	if (*input_str == '|')
		return (1);
	while (*input_str != '\0')
	{
		if (*input_str == '\'' || *input_str == '"')
			input_str = skip_quoted_part(input_str);
		else if (*input_str != '\'' && *input_str != '"' && *input_str != '|')
			input_str = skip_unquoted_part(input_str);
		else if (*input_str == '|')
		{
			input_str++;
			if (*input_str == '|' || check_str_whitespaces(input_str))
				return (1);
			while (*input_str && check_char_whitespaces(*input_str))
					input_str++;
			if (*input_str && *input_str == '|')
				return (1);
		}
	}
	return (0);
}

int check_missing_quotes(char *input_str)
{
	char	quote;

	quote = 0;
	while (*input_str != '\0')
	{
		if (*input_str == '\'' || *input_str == '"')
		{
			if (quote == 0)
				quote = *input_str;
			else if (quote == *input_str)
				quote = 0;
		}
		input_str++;
	}
	if (quote != 0)
		return (1);
	return (0);
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

int input_pre_validation(char *input_str)
{
	if (check_str_whitespaces(input_str))
	{
		printf("whitespace error\n");
		return (1);
	}
	if (check_invalid_pipe(input_str))
	{
		printf("pipe error\n");
		return (1);
	}
	if (check_missing_quotes(input_str))
	{
		printf("missing quote error\n");
		return (1);
	}
	if (check_backslash(input_str))
	{
		printf("invalid backslash\n");
		return (1);
	}
	return (0);
}

//printf("after inside unquoted part str: %c \n", *input_str);
