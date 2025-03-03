#include "minishell.h"

void	add_new_token(t_token **head_token, t_token *new_token)
{
	t_token *temp_token;

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


t_token *delete_empty_token(t_token *head_token)
{
	t_token *current_token;
	t_token	*prev_token;
	t_token	*temp;

	if (!head_token)
		return (NULL);
	prev_token = NULL;
	current_token  =  head_token;
	while (current_token)
	{
		if (current_token->tok_type == EMPTY)
		{
			temp = current_token;
			if (prev_token == NULL)
				head_token  = current_token->next;
			else
				prev_token->next = current_token->next;
			current_token = current_token->next;
			free(temp->tok_value);  //make a function
			free(temp);
		}
		else
		{
			prev_token  = current_token;
			current_token  = current_token->next;
		}
	}
	return (head_token);
}

t_token *assign_file_deli_tokens(t_token *head_token)
{
	t_token *current_token;

	if (!head_token)
		return (NULL);
	current_token = head_token;
	while (current_token)
	{
		if (current_token->tok_type == REDIRECT
			&& ft_strcmp(current_token->tok_value, "<<")
			&& current_token->next->tok_type == CMD)
			current_token->next->tok_type = DELIMETER;
		else if (current_token->tok_type == REDIRECT
			&& !ft_strcmp(current_token->tok_value, "<<")
			&& current_token->next->tok_type == CMD)
			current_token->next->tok_type = FILENAME;
		// else
		// 	return (NULL); // print error??
		current_token = current_token->next;
	}
	return(head_token);
}
