#include  "minishell.h"

int get_splitted_cmd_len(t_token *token_list)
{
	int	len;
	t_token *current_token;

	len =  0;
	current_token = token_list;
	while (current_token)
	{
		if (current_token->tok_type == CMD)
			len++;
		current_token = current_token->next;
	}
	return (len);
}

char	*create_splitted_cmd(t_token *token_list)
{
	int	len;
	t_token *current_token;

	current_token = token_list;
	len = get_splitted_cmd_len(token_list);
	if (!token_list)
		return (NULL);
	while (condition)
	{
		/* code */
	}
	

}
