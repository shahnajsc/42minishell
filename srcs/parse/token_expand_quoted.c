/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_quoted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:34:43 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 20:18:23 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_double_quoted(t_mshell *mshell, char *tok_val, int *i)
{
	(*i)++;
	while (tok_val[*i] && tok_val[*i] != '"')
	{
		if (tok_val[*i] == '$' && tok_val[*i + 1])
		{
			if (tok_val[*i + 1] == '?')
				tok_val = get_var_expanded(tok_val, ft_itoa(mshell->exit_code),
						"?", i);
			else if (!check_char_whitespaces(tok_val[*i + 1])
				&& tok_val[*i + 1] != '"')
				tok_val = get_expanded_token(mshell, tok_val, i);
			else
				(*i)++;
		}
		else
			(*i)++;
	}
	(*i)++;
	return (tok_val);
}

int	quote_skip(const char *input, char quote, int i)
{
	i++;
	while (input[i] && input[i] != quote)
		i++;
	i++;
	return (i);
}

char	*remove_quote(char *tok_val, int start, int end)
{
	char	*new_token;
	int		new_len;

	new_len = ft_strlen(tok_val);
	new_token = ft_calloc(new_len - 1, sizeof(char));
	if (!new_token)
		return (NULL);
	ft_strlcpy(new_token, tok_val, start + 1);
	ft_strlcpy(new_token + start, tok_val + start + 1, end - start - 1);
	ft_strlcpy(new_token + end - 2, tok_val + end, new_len - end + 2);
	free(tok_val);
	return (new_token);
}

char	*expand_quoted_token(t_mshell *mshell, char *tok_val, int *i)
{
	int	start;
	int	end;

	start = *i;
	if (tok_val[*i] && tok_val[*i] == '\'')
	{
		*i = quote_skip(tok_val, '\'', *i);
		end = *i;
		tok_val = remove_quote(tok_val, start, end);
		*i = end - 2;
	}
	else if (tok_val[*i] && tok_val[*i] == '"')
	{
		tok_val = expand_double_quoted(mshell, tok_val, i);
		if (!tok_val)
			return (NULL);
		end = *i;
		tok_val = remove_quote(tok_val, start, end);
		if (!tok_val)
			return (NULL);
		*i = end - 2;
	}
	return (tok_val);
}
