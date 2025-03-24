#include "minishell.h"

int	check_char_is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	check_char_is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

char	*get_token_envkey(char *token_value, int i)
{
	char	*env_key;
	int		key_end;
	int		key_start;

	if (!token_value)
		return (NULL);
	i++;
	key_start = i;
	key_end = 0;
	env_key = NULL;
	while (token_value[i + key_end] && !ft_strchr("$?\"'/\\\n", token_value[i + key_end]))
	{
		key_end++;
	}
	if ((key_start + key_end) > key_start)
		env_key = ft_substr(token_value, key_start, key_end);
	if (!env_key)
		return (NULL);
	return (env_key);
}

char	*get_env_key_value(t_mshell *mshell, char *env_key)
{
	int		i;
	char	*env_key_value;

	if (!env_key)
		return (NULL);
	i = 0;
	env_key_value = NULL;
	while (mshell->env[i].key)
	{
		if (ft_strcmp(mshell->env[i].key, env_key) == 0)
		{
			env_key_value = ft_strdup(mshell->env[i].value);
			return (env_key_value);
		}
		i++;
	}
	if (!env_key_value)
		env_key_value = ft_strdup("");
	return (env_key_value);
}
