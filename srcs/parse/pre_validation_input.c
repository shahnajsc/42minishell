#include "minishell.h"

int	check_backslash(t_mshell *mshell, char *input_str)
{
	while (*input_str != '\0')
	{
		if (*input_str && (*input_str == '\'' || *input_str == '"'))
			input_str = skip_quoted_part(input_str);
		else if (*input_str && *input_str == '\\')
			return (syntax_pre_error(mshell, ERR_BACK_S, input_str));
		else
			input_str++;
	}
	return (EXIT_SUCCESS);
}

int	check_invalid_redirection(t_mshell *mshell, char *input)
{
	char	rd_current;
	int		rd_count;

	while (*input != '\0')
	{
		if (*input == '\'' || *input == '"')
			input = skip_quoted_part(input);
		else if (*input == '<' || *input == '>')
		{
			rd_current = *input;
			rd_count = 0;
			while (*input == rd_current && ++rd_count)
				input++;
			if (rd_count > 2)
				return (syntax_pre_error(mshell, ERR_RD, (input - rd_count)));
			while (*input && check_char_whitespaces(*input))
				input++;
			if (!*input || *input == '\n' || ft_strchr("<>|", *input))
				return (syntax_pre_error(mshell, ERR_RD, input));
		}
		else
			input++;
	}
	return (EXIT_SUCCESS);
}

int	check_invalid_pipe(t_mshell *mshell, char *input_str)
{
	while (*input_str && check_char_whitespaces(*input_str))
		input_str++;
	if (*input_str && *input_str == '|')
		return (syntax_pre_error(mshell, ERR_P, (input_str + 1)));
	while (*input_str)
	{
		if (*input_str == '\'' || *input_str == '"')
			input_str = skip_quoted_part(input_str);
		else if (*input_str != '\'' && *input_str != '"' && *input_str != '|')
		{
			input_str = skip_unquoted_part(input_str);
		}
		else if (*input_str == '|')
		{
			input_str++;
			if (*input_str == '|' || check_str_whitespaces(input_str))
				return (syntax_pre_error(mshell, ERR_P, input_str));
			while (*input_str && check_char_whitespaces(*input_str))
				input_str++;
			if (*input_str && *input_str == '|')
				return (syntax_pre_error(mshell, ERR_P, (input_str + 1)));
		}
	}
	return (EXIT_SUCCESS);
}

int	check_missing_quotes(t_mshell *mshell, char *input_str)
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
		return (syntax_pre_error(mshell, ERR_Q, &quote));
	return (EXIT_SUCCESS);
}

int	pre_validation_input(t_mshell *mshell, char *input_str)
{
	if (check_str_whitespaces(input_str))
		return (EXIT_FAILURE); // check for actual error mg
	if (check_missing_quotes(mshell, input_str))
		return (EXIT_FAILURE);
	if (check_invalid_pipe(mshell, input_str))
		return (EXIT_FAILURE);
	if (check_backslash(mshell, input_str))
		return (EXIT_FAILURE);
	if (check_invalid_redirection(mshell, input_str))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//************************************** */
// why |> fdf is working???


//printf("after inside unquoted part str: %c \n", *input_str);
