#include "minishell.h"

t_token *expand_token_values(t_token *head_token)
{
	t_token *current_token;

	if (!head_token)
		return ( NULL);
	current_token = head_token;
	while (current_token)
	{
		if (current_token->tok_type == CMD)
			current_token->tok_value = expand_cmd_token();
		else if (current_token->tok_type == FILENAME)
			current_token->tok_value = expand_filename_token();
		else if (current_token->tok_type == DELIMETER)
			current_token->tok_value = expand_delimeter_token();
		current_token = current_token->next;
	}
	return (head_token);
}
