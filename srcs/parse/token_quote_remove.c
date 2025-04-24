/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:54:08 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 16:41:22 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*deli_quote_remove(t_cmd *cmd, char *tok_value)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (tok_value[i])
	{
		if (check_char_is_quote(tok_value[i]))
		{
			start = i;
			end = quote_skip(tok_value, tok_value[i], i);
			tok_value = remove_quote(tok_value, start, end);
			i = end - 2;
			cmd->is_hd_quote = 1;
		}
		else
			i++;
	}
	return (tok_value);
}

t_token	*remove_deli_quotes(t_mshell *mshell, t_token *head_token, int cmd_id)
{
	t_token	*current_token;

	if (!head_token)
		return (NULL);
	current_token = head_token;
	while (current_token)
	{
		if (current_token->tok_type == DELIMETER)
		{
			current_token->tok_value = deli_quote_remove(&mshell->cmds[cmd_id],
					current_token->tok_value);
		}
		current_token = current_token->next;
	}
	return (head_token);
}
