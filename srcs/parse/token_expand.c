#include "minishell.h"

char	*get_var_expanded(char *token, char *env_value, char *env_key, int *i)
{
	char	*new_token;
	int		value_len;
	int		key_len;
	int		new_len;


	value_len = ft_strlen(env_value);
	key_len  = ft_strlen(env_key);
	new_len = ft_strlen(token) + value_len - key_len;
	new_token = ft_calloc(new_len + 1, sizeof(char));
	if (!new_token)
		return (NULL);
	ft_strlcpy(new_token, token, *i + 1);
	if (env_value)
		ft_strlcpy(new_token + *i, env_value, *i + value_len + 1);
	ft_strlcpy(new_token + *i + value_len, token + *i + ft_strlen(env_key) + 1, new_len + 1);
	*i += value_len;
	free(token);
	free(env_value);
	return (new_token);
}

char	*get_expanded_token(t_mshell *mshell, char *token_value, int *i)
{
	char	*env_key;
	char	*env_key_value;
	char	*expanded_token;

	env_key = get_token_envkey(token_value, *i);
	if (!env_key)
		return (NULL);
	env_key_value = get_env_key_value(mshell, env_key);
	if (!env_key_value)
		return (free(env_key), NULL);
	expanded_token = get_var_expanded(token_value, env_key_value, env_key, i);
	if (!expanded_token)
		return (token_value);
	free(env_key);
	return (expanded_token);
}

char	*replace_var(char *token, int *i)
{
	char	*new_token;
	int		new_len;

	new_len = ft_strlen(token) - 1;
	new_token = ft_calloc(new_len + 1, sizeof(char));
	if (!new_token)
		return (NULL);
	ft_strlcpy(new_token, token, *i + 1);
	ft_strlcpy(new_token + *i, token + *i + 1, new_len + 1);
	free(token);
	return (new_token);
}

char	*expand_text_token(t_mshell *mshell, char *token_value)
{
	int		i;

	if (!token_value)
		return (NULL);
	i = 0;
	if (token_value[i] == '\'')
		return (token_value);
	while (token_value[i])
	{
		if (token_value[i] == '$' && token_value[i + 1] && token_value[i + 1] == '$')
			token_value = get_var_expanded(token_value, ft_itoa(getpid()), "&", &i);
		else if (token_value[i] == '$' && token_value[i + 1] && !ft_strchr("$/\"'", token_value[i + 1]))
		{
			printf("in not quote\n");
			if (check_char_whitespaces(token_value[i + 1]) || token_value[i + 1] == '?')
			{
				if (check_char_whitespaces(token_value[i + 1]))
					i++;
				else
					token_value = get_var_expanded(token_value, ft_itoa(mshell->exit_code), "?", &i);
			}
			else
				token_value = get_expanded_token(mshell, token_value, &i);
		}
		else
		{
			if (token_value[i] == '$' && ft_strchr("\"'", token_value[i + 1]))
			{
				if (token_value[i + 1] == '/')
					printf("is quote\n");
				printf("in quote %d c=%c\n", check_char_is_quote('\''), token_value[i]);
				token_value = replace_var(token_value, &i);
			}
			else
				i++;
		}

	}
	return (token_value);
}

t_token	*expand_token_values(t_mshell *mshell, t_token *head_token)
{
	t_token	*current_token;

	if (!head_token)
		return (NULL);
	current_token = head_token;
	while (current_token)
	{
		if (current_token->tok_type == CMD || current_token->tok_type == FILENAME)
			current_token->tok_value = expand_text_token(mshell, current_token->tok_value);
		if (!current_token->tok_value)
			return (NULL);
		current_token = current_token->next;
	}
	return (head_token);
}

//cases to check: $, $$ , $/, $1, $123 , echo $$HOME
