#include "minishell.h"

int	check_char_is_token(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

char	*get_quoted_token_value(char *cmd_str, int *i)
{
	char	*token_value;
	int		temp_i;
	int		value_size;
	char	quote_type;

	token_value = NULL;
	quote_type = cmd_str[*i];
	value_size = 1;
	temp_i = *i; // i or *i??
	temp_i++;
	while (cmd_str[temp_i] && cmd_str[temp_i] != quote_type)
	{
		temp_i++;
		value_size++;
	}
	if (cmd_str[temp_i] && cmd_str[temp_i] == quote_type)
		value_size++;
	token_value = ft_strndup(&cmd_str[*i], value_size);
	*i = (*i) + value_size;// update *i value
	return (token_value);
}

char *get_unquoted_token_value(char *cmd_str, int *i)
{
	char	*token_value;
	int		temp_i;
	int		value_size;

	token_value = NULL;
	value_size = 0;
	temp_i = *i; // i or *i??
	while (cmd_str[temp_i] && !check_char_is_quote(cmd_str[temp_i])
		&& !check_char_is_token(cmd_str[temp_i]) && check_char_whitespaces(cmd_str[temp_i]))
	{
		temp_i++;
		value_size++;
	}
	token_value = ft_strndup(&cmd_str[*i], value_size);
	*i = temp_i;// update *i value
	return (token_value);
}

char *get_other_token_value(int *i, t_token_type t_type)
{
	char	*token_value;

	token_value = NULL;
	if (t_type == RD_IN)
		token_value = ft_strdup("<");
	else if (t_type == RD_HEREDOC)
		token_value = ft_strdup("<<");
	else if (t_type == RD_OUT)
		token_value = ft_strdup(">");
	else if (t_type == RD_APPEND)
		token_value = ft_strdup(">>");
	if (!token_value)
		return (NULL);
	if (t_type == RD_IN || t_type == RD_OUT)
		(*i)++;
	else if (t_type == RD_HEREDOC || t_type == RD_APPEND)
		(*i) += 2;
	return (token_value);
}

t_token	*create_other_token(int *i, t_token_type t_type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL); //what to return?
	new_token->tok_value = get_other_token_value(i, t_type);
	if (!new_token->tok_value)
		return (NULL);
	new_token->tok_type = t_type;
	new_token->next = NULL;
	return (new_token);
}

t_token *create_cmd_token(char *cmd_str, int *i, t_token_type t_type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL); //what to return?
	if (check_char_is_quote(cmd_str[*i]))
		new_token->tok_value = get_quoted_token_value(cmd_str, i);
	else
		new_token->tok_value = get_unquoted_token_value(cmd_str, i);
	if (!new_token->tok_value)
		return (NULL);
	new_token->tok_type = t_type;
	new_token->next = NULL;
	return (new_token);
}
