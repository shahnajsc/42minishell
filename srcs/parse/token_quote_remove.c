#include "minishell.h"

char	*remove_quote(char *tok_value)
{
	int		i;
	int		len;
	char	*new_value;

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

t_token	*remove_token_quotes(t_mshell *mshell, t_token *head_token, int cmd_id)
{
	t_token	*current_token;

	if (!head_token)
		return (NULL);
	current_token = head_token;
	while (current_token)
	{
		if (check_char_is_quote(current_token->tok_value[0]))
		{
			if (current_token->tok_type == DELIMETER)
				mshell->cmds[cmd_id].is_here_exp = 1;
			current_token->tok_value = remove_quote(current_token->tok_value);
		}
		if (!current_token->tok_value)
			return (NULL);
		current_token = current_token->next;
	}
	return (head_token);
}
