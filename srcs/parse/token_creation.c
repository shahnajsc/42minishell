/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:53:23 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 13:43:59 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_quoted_token_value(char *cmd_str, int *i)
{
	char	*token_value;
	int		temp_i;
	int		value_size;
	char	quote_type;

	quote_type = cmd_str[*i];
	value_size = 0;
	temp_i = (*i) + 1;
	while (cmd_str[temp_i] && cmd_str[temp_i] != quote_type)
		temp_i++;
	if (cmd_str[temp_i] && cmd_str[temp_i] == quote_type)
		temp_i++;
	value_size = temp_i - (*i);
	token_value = ft_strndup(&cmd_str[*i], value_size);
	*i = temp_i;
	return (token_value);
}

static char	*get_unquoted_token_value(char *cmd_str, int *i)
{
	char	*token_value;
	int		temp_i;
	int		value_size;

	token_value = NULL;
	temp_i = *i;
	if (check_char_whitespaces(cmd_str[temp_i]))
	{
		while (cmd_str[temp_i] && !check_char_is_quote(cmd_str[temp_i])
			&& !check_char_is_redirect(cmd_str[temp_i])
			&& check_char_whitespaces(cmd_str[temp_i]))
			temp_i++;
	}
	else
	{
		while (cmd_str[temp_i] && !check_char_is_quote(cmd_str[temp_i])
			&& !check_char_is_redirect(cmd_str[temp_i])
			&& !check_char_whitespaces(cmd_str[temp_i]))
			temp_i++;
	}
	value_size = temp_i - (*i);
	token_value = ft_strndup(&cmd_str[*i], value_size);
	*i = temp_i;
	return (token_value);
}

static t_token	*create_redirect_token(char *cmd_str, int *i)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->tok_value = get_redir_token_value(cmd_str, i);
	if (!new_token->tok_value)
		return (NULL);
	new_token->tok_type = REDIRECT;
	new_token->next = NULL;
	return (new_token);
}

static t_token	*create_str_token(char *cmd_str, int *i, t_token_type t_type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
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

t_token	*create_tokens_list(t_mshell *mshell, char *cmd_str, int cmd_id)
{
	t_token			*head_token;
	t_token			*new_token;
	t_token_type	tok_type;
	int				i;

	i = 0;
	head_token = NULL;
	while (cmd_str[i] != '\0')
	{
		tok_type = get_token_type(cmd_str, i);
		if (tok_type == CMD || tok_type == EMPTY)
			new_token = create_str_token(cmd_str, &i, tok_type);
		else
			new_token = create_redirect_token(cmd_str, &i);
		if (!new_token)
			return (NULL);
		add_new_token(&head_token, new_token);
	}
	head_token = post_process_token(mshell, head_token, cmd_id);
	if (!head_token)
		return (NULL);
	return (head_token);
}
