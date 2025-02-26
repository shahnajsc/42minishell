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
