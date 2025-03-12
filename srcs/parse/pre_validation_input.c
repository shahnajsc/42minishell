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
	mshell->exit_code = 0;
	return (0);
}

int	check_invalid_redirection(t_mshell *mshell, char *input_str)
{
	char	rd_current;
	int		rd_count;

	while (*input_str != '\0')
	{
		if (*input_str == '\'' || *input_str == '"')
			input_str = skip_quoted_part(input_str);
		else if (*input_str == '<' || *input_str == '>')
		{
			rd_current = *input_str;
			rd_count = 0;
			while (*input_str == rd_current && ++rd_count)
				input_str++;
			if (rd_count > 2)
				return (syntax_pre_error(mshell, ERR_RD, (input_str - rd_count)));
			while (*input_str && check_char_whitespaces(*input_str))
				input_str++;
			if (!*input_str || *input_str == '\n' || ft_strchr("<>|", *input_str))
				return (syntax_pre_error(mshell, ERR_RD, input_str));
		}
		else
			input_str++;
	}
	mshell->exit_code = 0;
	return (0);
}
//cat <>  fff

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
	mshell->exit_code = 0;
	return (0);
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
	mshell->exit_code = 0;
	return (0);
}

int	input_pre_validation(t_mshell *mshell, char *input_str)
{
	if (check_str_whitespaces(input_str))
		return (syntax_pre_error(mshell, ERR_COMN, NULL)); // check for actual error mg
	if (check_missing_quotes(mshell, input_str))
		return (1);
	if (check_invalid_pipe(mshell, input_str))
		return (1);
	if (check_backslash(mshell, input_str))
		return (1);
	if (check_invalid_redirection(mshell, input_str))
		return (1);
	mshell->exit_code = 0;// check is it needed???
	return (0);
}

//************************************** */
// why |> fdf is working???


//printf("after inside unquoted part str: %c \n", *input_str);
