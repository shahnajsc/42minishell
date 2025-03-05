#include "minishell.h"

char	*get_token_envkey(char *token_value, int i)
{
	char	*env_key;
	int		key_end;
	int		key_start;
	if (!token_value)
		return (NULL);
	key_start = i;
	key_end = 0;
	while (token_value[i +  key_end] && !ft_strchr("$?\"'/", token_value[i + key_end]))
	{
		key_end++;
	}
	if ((key_start + key_end) > key_start)
		env_key = ft_substr(token_value, key_start, key_end);
	else
		env_key = ft_strdup("");
	return (env_key);
}
char *get_env_key_value(t_mshell *mshell, char *env_key)
{
	int	i;
	char *env_key_value;

	if (!env_key)
		return (NULL);
	i = 0;
	env_key_value = NULL;
	while (mshell->env[i].key)
	{
		if (ft_strcmp(mshell->env[i].key, env_key) == 0)
		{
			env_key_value = ft_strdup(mshell->env[i].value);
			break ;
		}
		i++;
	}
	if (!env_key_value)
		env_key_value = ft_strdup("");
	return (env_key_value);
}


char	*get_expanded_token(t_mshell *mshell, char *token_value,  int *i)
{
	char	*env_key;
	char	*env_key_value;
	char	*expanded_token;
	//int		token_new_len;
	// char	*value_remain;

	expanded_token = ft_substr(token_value, 0, *i);
	(*i)++;
	printf("i value before key[%d]\n", *i);
	env_key = get_token_envkey(token_value, *i);
	printf("i value after key[%d]\n", *i);
	env_key_value = get_env_key_value(mshell, env_key);
	//token_new_len = (ft_strlen(token_value) + ft_strlen(env_key))
	expanded_token = ft_strjoin(expanded_token, env_key_value);
	*i = ft_strlen(expanded_token);
	printf("i value after strjoin[%d]\n", *i);
	return (expanded_token); //wrong value
}
//printf("env_key[%s]\n", env_key);
//printf("env_key_value[%s]\n", env_key_value);

char	*expand_text_token(t_mshell *mshell, char *token_value)
{
	int	i;

	if (!token_value)
		return (NULL);
	i = 0;
	if (token_value[i] == '\'')
		return (token_value);
	while (token_value[i])
	{
		while (token_value[i] && token_value[i] != '$')
			i++;
		if (token_value[i] == '$' && token_value[i +  1])
			token_value = get_expanded_token(mshell, token_value, &i);
	}
	printf("exp token[%s]\n", token_value);
	if (!token_value)
		return (token_value);
	return (token_value);
}

t_token *expand_token_values(t_mshell *mshell, t_token *head_token)
{
	t_token *current_token;
	// char 	*value;

	if (!head_token)
		return ( NULL);
	current_token = head_token;
	while (current_token)
	{
		if (current_token->tok_type == CMD || current_token->tok_type == FILENAME)
			current_token->tok_value = expand_text_token(mshell, current_token->tok_value);
		// else if (current_token->tok_type == DELIMETER)
		// 	current_token->tok_value = expand_delimeter_token(current_token->tok_value);
		// if (check_char_is_quote(current_token->tok_value[0]))
		// 	current_token->tok_value = remove_quote(mshell, current_token->tok_value);
		current_token = current_token->next;
	}
	return (head_token);
}
