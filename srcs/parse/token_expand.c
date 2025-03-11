#include "minishell.h"

char	*get_var_expanded(char *token, char *env_value, char *env_key, int *i)
{
	int		new_len;
	char	*new_token;
	int		env_len;

	env_len = ft_strlen(env_value);
	new_len = ft_strlen(token) + env_len - ft_strlen(env_key);
	new_token = ft_calloc(new_len + 1, sizeof(char));
	if (!new_token)
		return (NULL);
	ft_strlcpy(new_token, token, *i + 1);
	if (env_value)
		ft_strlcpy(new_token + *i, env_value, *i + env_len + 1);
	ft_strlcpy(new_token + *i + env_len, token + *i + ft_strlen(env_key) + 1, new_len + 1);
	*i += env_len;
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
	free(env_key);
	free(env_key_value);
	free(token_value);
	if (!expanded_token)
		return (NULL);
	return (expanded_token);
}

char	*expand_text_token(t_mshell *mshell, char *token_value)
{
	int		i;
	char	*exit_code;

	if (!token_value)
		return (NULL);
	i = 0;
	exit_code = ft_itoa(mshell->exit_code);
	if (!exit_code)
		return (NULL);
	if (token_value[i] == '\'')
		return (token_value);
	while (token_value[i])
	{
		// if (token_value[i] == '$' && token_value[i +  1] && token_value[i + 1] == '$')
		// 	what??
		if (token_value[i] == '$' && token_value[i + 1] && !ft_strchr("$/", token_value[i + 1]))
		{
			if (check_char_whitespaces(token_value[i + 1]) || token_value[i + 1] == '?')
				token_value = get_var_expanded(token_value, exit_code, "?", &i);
			else
				token_value = get_expanded_token(mshell, token_value, &i);
		}
		else
			i++;
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
