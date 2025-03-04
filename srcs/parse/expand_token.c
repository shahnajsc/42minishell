#include "minishell.h"

char	**expand_cmd_token(t_mshell *mshell, char *token_value)
{
	int	i;
	char	*env_key;
	char	*key_value;
	char	*value_remain;

	if (!token_value)
		return (NULL);
	i = 0;
	value_remain = NULL;
	while (token_value[i])
	{
		if (token_value[i] == '\'')
			return (token_value);
		else if (token_value[i] == '"' || token_value[i] == '$')
		{
			if (token_value[i] == '"')
				i++;
			if (token_value[i] == '$')
			{
				env_key = get_token_envkey(mshell, token_value[i], value_remain);
				key_value = get_token_envvalue(mshell, env_key);
			}
		}
		else
			i++;
	}
}

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
			current_token->tok_value = expand_delimeter_token(current_token->tok_value);
		current_token = current_token->next;
	}
	return (head_token);
}
