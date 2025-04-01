#include "minishell.h"

void	add_new_token(t_token **head_token, t_token *new_token)
{
	t_token	*temp_token;

	if (!new_token)
		return ;
	if (!*head_token)
	{
		*head_token = new_token;
		return ;
	}
	temp_token = *head_token;
	while (temp_token->next)
		temp_token = temp_token->next;
	temp_token->next = new_token;
}

t_token	*delete_empty_token(t_token *head_token)
{
	t_token	*current_token;
	t_token	*prev_token;
	t_token	*temp;

	if (!head_token)
		return (NULL);
	prev_token = NULL;
	current_token = head_token;
	while (current_token)
	{
		if (current_token->tok_type == EMPTY)
		{
			temp = current_token;
			if (prev_token == NULL)
				head_token = current_token->next;
			else
				prev_token->next = current_token->next;
			current_token = current_token->next;
			free(temp->tok_value); //make a function
			free(temp);
		}
		else
		{
			prev_token = current_token;
			current_token = current_token->next;
		}
	}
	return (head_token);
}

char	*get_redir_token_value(char *cmd_str, int *i)
{
	char	*tok_val;

	tok_val = NULL;
	if (cmd_str[*i] == '<' && cmd_str[*i + 1] == '<')
		tok_val = ft_strdup("<<");
	else if (cmd_str[*i] == '<')
		tok_val = ft_strdup("<");
	else if (cmd_str[*i] == '>' && cmd_str[*i + 1] == '>')
		tok_val = ft_strdup(">>");
	else if (cmd_str[*i] == '>')
		tok_val = ft_strdup(">");
	if (!tok_val)
		return (NULL);
	if (ft_strcmp(tok_val, "<") == 0 || ft_strcmp(tok_val, ">") == 0)
		(*i)++;
	else if (ft_strcmp(tok_val, "<<") == 0 || ft_strcmp(tok_val, ">>") == 0)
		(*i) = *i + 2;
	return (tok_val);
}

// t_token *delete_empty_token(t_token *head_token)
// {
// 	t_token *current = head_token, *prev = NULL, *temp;

// 	while (current)
// 	{
// 		if (current->tok_type == EMPTY)
// 		{
// 			temp = current;
// 			if (!prev)
// 				head_token = current->next;
// 			else
// 				prev->next = current->next;
// 			current = current->next;
// 			free(temp->tok_value);
// 			free(temp);
// 		}
// 		else
// 		{
// 			prev = current;
// 			current = current->next;
// 		}
// 	}
// 	return (head_token);
// }
