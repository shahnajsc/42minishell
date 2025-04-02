/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:54:23 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/02 17:23:42 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_token_envkey(char *tok_val, int i)
{
	char	*env_key;
	int		key_end;
	int		key_start;

	if (!tok_val)
		return (NULL);
	i++;
	key_start = i;
	key_end = 0;
	env_key = NULL;
	while (tok_val[i + key_end] && !check_char_whitespaces(tok_val[i + key_end])
		&& !ft_strchr("$?\"'/\\\n", tok_val[i + key_end]))
	{
		key_end++;
	}
	if ((key_start + key_end) > key_start)
		env_key = ft_substr(tok_val, key_start, key_end);
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
	while (mshell->env[i].key != NULL)
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
