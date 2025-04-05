/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_post_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:53:58 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 16:31:05 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*update_file_deli_token(t_token *token_list, int is_heredoc)
{
	t_token	*current_token;

	current_token = token_list;
	while (current_token && current_token->tok_type == EMPTY)
		current_token = current_token->next;
	while (current_token && current_token->tok_type == CMD)
	{
		if (is_heredoc)
			current_token->tok_type = DELIMETER;
		else
			current_token->tok_type = FILENAME;
		current_token = current_token->next;
	}
	return (current_token);
}

static t_token	*assign_file_deli_tokens(t_token *head_token)
{
	t_token	*current_token;
	int		is_heredoc;

	if (!head_token)
		return (NULL);
	current_token = head_token;
	while (current_token)
	{
		if (current_token->tok_type == REDIRECT && current_token->next)
		{
			is_heredoc = 0;
			if (ft_strcmp(current_token->tok_value, "<<") == 0)
				is_heredoc = 1;
			current_token = current_token->next;
			current_token = update_file_deli_token(current_token, is_heredoc);
		}
		else
			current_token = current_token->next;
	}
	return (head_token);
}

t_token	*post_process_token(t_mshell *mshell, t_token *head_token, int cmd_id)
{
	if (!head_token)
		return (NULL);
	head_token = assign_file_deli_tokens(head_token);
	head_token = merge_consequtive_token(head_token);
	head_token = expand_token_values(mshell, head_token);
	if (head_token)
		head_token = delete_empty_token(head_token);
	head_token = remove_deli_quotes(mshell, head_token, cmd_id);
	if (!head_token)
		return (NULL);
	return (head_token);
}
