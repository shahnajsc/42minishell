#include "minishell.h"

t_token	*merge_tokens(t_token *main_token, t_token *to_merge)
{
	char	*temp_main_value;

	if (!to_merge)
		return (main_token);
	temp_main_value = main_token->tok_value;
	//temp = to_merge;
	main_token->tok_value = ft_strjoin(main_token->tok_value, to_merge->tok_value);
	if (!main_token->tok_value)
		return (NULL);
	main_token->next = to_merge->next;
	free(temp_main_value);
	free(to_merge->tok_value);
	free(to_merge);
	return (main_token);
}

t_token	*merge_consequtive_token(t_token *head_token)
{
	t_token			*current_token;
	t_token_type	type;

	if (!head_token)
		return (NULL);
	current_token = head_token;
	while (current_token)
	{
		if (current_token->tok_type != EMPTY && current_token->tok_type != REDIRECT)
		{
			type = current_token->tok_type;
			while (current_token->next && current_token->next->tok_type == type)
			{
				current_token = merge_tokens(current_token, current_token->next);
				if (!current_token->next)
					break ;
			}
		}
		current_token = current_token->next;
	}
	return (head_token);
}
