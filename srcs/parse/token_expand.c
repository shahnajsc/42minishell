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
	ft_strlcpy(new_token + *i + value_len, token + *i + ft_strlen(env_key) + 1,
		new_len + 1);
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

char	*expand_text_token(t_mshell *mshell, char *tok_val)
{
	int		i;

	if (!tok_val)
		return (NULL);
	i = 0;
	if (tok_val[i] == '\'')
		return (tok_val);
	while (tok_val[i])
	{
		if (tok_val[i] == '$' && tok_val[i + 1] && tok_val[i + 1] == '$')
			tok_val = get_var_expanded(tok_val, ft_itoa(getpid()), "&", &i);
		else if (tok_val[i] == '$' && tok_val[i + 1]
			&& !ft_strchr("$/\"'", tok_val[i + 1]))
		{
			if (check_char_whitespaces(tok_val[i + 1]) || tok_val[i + 1] == '?')
			{
				if (check_char_whitespaces(tok_val[i + 1]))
					i++;
				else
					tok_val = get_var_expanded(tok_val, ft_itoa(mshell->exit_code), "?", &i);
			}
			else
				tok_val = get_expanded_token(mshell, tok_val, &i);
		}
		else
		{
			if (tok_val[i] == '$' && ft_strchr("\"'", tok_val[i + 1]))
				tok_val = replace_var(tok_val, &i);
			else
				i++;
		}

	}
	return (tok_val);
}

t_token	*expand_token_values(t_mshell *mshell, t_token *head_token)
{
	t_token	*cur_tok;

	if (!head_token)
		return (NULL);
	cur_tok = head_token;
	while (cur_tok)
	{
		if (cur_tok->tok_type == CMD || cur_tok->tok_type == FILENAME)
			cur_tok->tok_value = expand_text_token(mshell, cur_tok->tok_value);
		if (!cur_tok->tok_value)
			return (NULL);
		cur_tok = cur_tok->next;
	}
	return (head_token);
}

//cases to check: $, $$ , $/, $1, $123 , echo $$HOME
