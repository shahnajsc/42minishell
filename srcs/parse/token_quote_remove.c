/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:54:08 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 13:49:17 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quote(char *tok_value)
{
	int		i;
	int		len;
	char	*new_value;

	i = 0;
	len = ft_strlen(tok_value);
	new_value = ft_calloc(len - 1, sizeof(char));
	if (!new_value)
		return (NULL);
	while (i < len - 2)
	{
		new_value[i] = tok_value[i + 1];
		i++;
	}
	new_value[i] = '\0';
	free(tok_value);
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
		if (current_token->tok_value
			&& check_char_is_quote(current_token->tok_value[0]))
		{
			if (current_token->tok_type == DELIMETER)
				mshell->cmds[cmd_id].is_hd_quote = 1;
			current_token->tok_value = remove_quote(current_token->tok_value);
		}
		current_token = current_token->next;
	}
	return (head_token);
}
