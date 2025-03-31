#include "minishell.h"

t_token	*merge_tokens(t_token *main_tok, t_token *to_merge)
{
	char	*temp_main_value;

	if (!to_merge)
		return (main_tok);
	temp_main_value = main_tok->tok_value;
	//temp = to_merge;
	main_tok->tok_value = ft_strjoin(main_tok->tok_value, to_merge->tok_value);
	if (!main_tok->tok_value)
		return (NULL);
	main_tok->next = to_merge->next;
	free(temp_main_value);
	free(to_merge->tok_value);
	free(to_merge);
	return (main_tok);
}

t_token	*merge_consequtive_token(t_token *head_token)
{
	t_token			*cur_tok;
	t_token_type	type;

	if (!head_token)
		return (NULL);
	cur_tok = head_token;
	while (cur_tok)
	{
		if (cur_tok->tok_type != EMPTY && cur_tok->tok_type != REDIRECT)
		{
			type = cur_tok->tok_type;
			while (cur_tok->next && cur_tok->next->tok_type == type)
			{
				cur_tok = merge_tokens(cur_tok, cur_tok->next);
				if (!cur_tok->next)
					break ;
			}
		}
		cur_tok = cur_tok->next;
	}
	return (head_token);
}
