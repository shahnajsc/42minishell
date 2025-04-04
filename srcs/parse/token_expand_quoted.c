/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:34:43 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/04 19:34:07 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_double_quoted(t_mshell *mshell, char *tok_val, int i)
{
	(i)++;
	while (tok_val[i] && tok_val[i] != '"')
	{
		if (tok_val[i] == '$')
		{
			if (tok_val[i + 1] == '?')
			{
				tok_val = get_var_expanded(tok_val, ft_itoa(mshell->exit_code), "?", &i);
				if (!tok_val)
					return (NULL);
			}
			else if (!check_char_whitespaces(tok_val[i + 1]) && tok_val[i + 1] != '"')
			{
				tok_val = get_expanded_token(mshell, tok_val, &i);
				if (!tok_val)
					return (NULL);
			}
		}
		else
			i++;
		i++;
	}
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

char	*expand_quoted_token(t_mshell *mshell, char *tok_val, int *i)
{
	if (tok_val[*i] && tok_val[*i] == '\'')
		*i = quote_skip(tok_val, '\'', *i);
	else if (tok_val[*i] && tok_val[*i] == '"')
	{
		tok_val = expand_double_quoted(mshell, tok_val, *i);
		*i = quote_skip(tok_val, '"', *i);
	}
	return (tok_val);
}
