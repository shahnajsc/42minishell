#include "minishell.h"

char	*get_quoted_token_value(char *cmd_str, int *i)
{
	char	*token_value;
	int		temp_i;
	int		value_size;
	char	quote_type;

	quote_type = cmd_str[*i];
	value_size = 0;
	temp_i = (*i) + 1; // i or *i??
	while (cmd_str[temp_i] && cmd_str[temp_i] != quote_type)
		temp_i++;
	if (cmd_str[temp_i] && cmd_str[temp_i] == quote_type)
		temp_i++;
	value_size = temp_i - (*i);
	token_value = ft_strndup(&cmd_str[*i], value_size);
	*i = temp_i;// update *i value
	return (token_value);
}

char *get_unquoted_token_value(char *cmd_str, int *i)
{
	char	*token_value;
	int		temp_i;
	int		value_size;

	token_value = NULL;
	temp_i = *i; // i or *i??
	if (check_char_whitespaces(cmd_str[temp_i]))
	{
		while (cmd_str[temp_i] && !check_char_is_quote(cmd_str[temp_i])
		&& !check_char_is_redirect(cmd_str[temp_i]) && check_char_whitespaces(cmd_str[temp_i]))
			temp_i++;
	}
	else
	{
		while  (cmd_str[temp_i] && !check_char_is_quote(cmd_str[temp_i])
		&& !check_char_is_redirect(cmd_str[temp_i]) && !check_char_whitespaces(cmd_str[temp_i]))
			temp_i++;
	}
	value_size = temp_i - (*i);
	token_value = ft_strndup(&cmd_str[*i], value_size);
	*i = temp_i;// update *i value
	return (token_value);
}

char *get_redir_token_value(char *cmd_str, int *i)
{
	char	*token_value;

	token_value = NULL;
	if (cmd_str[*i] == '<' && cmd_str[*i + 1] == '<')
		token_value = ft_strdup("<<");
	else if (cmd_str[*i] == '<')
		token_value = ft_strdup("<");
	else if (cmd_str[*i] == '>' && cmd_str[*i + 1] == '>')
		token_value = ft_strdup(">>");
	else if (cmd_str[*i] == '>')
		token_value = ft_strdup(">");
	if (!token_value)
		return (NULL);
	if (ft_strcmp(token_value, "<") == 0 || ft_strcmp(token_value, ">") == 0)
		(*i)++;
	else if (ft_strcmp(token_value, "<<") == 0 || ft_strcmp(token_value, ">>") == 0)
		(*i) = *i + 2;
	return (token_value);
}

t_token	*create_redirect_token(char *cmd_str, int *i)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL); //what to return?
	new_token->tok_value = get_redir_token_value(cmd_str, i);
	if (!new_token->tok_value)
		return (NULL);
	new_token->tok_type = REDIRECT;
	new_token->next = NULL;
	return (new_token);
}

t_token *create_str_token(char *cmd_str, int *i, t_token_type t_type)
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

char *remove_quote(char *tok_value)
{
	int	i;
	int len;
	char *new_value;

	i = 0;
	len = ft_strlen(tok_value);
	new_value = ft_calloc(len -1, sizeof(char));
	if (!new_value)
		return (NULL);
	while (i < len - 2)
	{
		new_value[i] = tok_value[i + 1];
		i++;
	}
	new_value[i] = '\0';
	return (new_value);
}

t_token *remove_token_quotes(t_token *head_token)
{
	t_token *current_token;

	if (!head_token)
		return (NULL);
	current_token = head_token;
	while (current_token)
	{
		if (check_char_is_quote(current_token->tok_value[0]))
			current_token->tok_value = remove_quote(current_token->tok_value);
		if (!current_token->tok_value)
			return (NULL);
		current_token = current_token->next;
	}
	return (head_token);
}


t_token	*create_tokens_list(t_mshell *mshell, char *cmd_str)
{
	t_token	*head_token;
	t_token	*new_token;
	t_token_type tok_type;
	int	i;

	i = 0;
	head_token = NULL;
	while (cmd_str[i] != '\0')
	{
		tok_type = get_token_type(cmd_str, i);
		if (tok_type == CMD || tok_type == EMPTY)
		{
			new_token = create_str_token(cmd_str, &i, tok_type);
		}
		else
			new_token = create_redirect_token(cmd_str, &i);
		if (!new_token)
			return (NULL); // free the whole token list
		add_new_token(&head_token, new_token);
	}
	head_token = assign_file_deli_tokens(head_token);
	head_token = expand_token_values(mshell, head_token);
	head_token = remove_token_quotes(head_token);
	//head_token = merge_consequtive_token(mshell, head_token);
	//head_token = delete_empty_token(head_token);
	if (!head_token)
		return (NULL);
	return (head_token);
}
