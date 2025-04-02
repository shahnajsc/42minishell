/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:54:40 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/01 20:54:42 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_token(t_token **head_token, t_token *new_token)
{
	t_token	*temp_token;

	if (!new_token)
		return ;
	if (!*head_token)
	{
		*head_token = new_token;
		return ;
	}
	temp_token = *head_token;
	while (temp_token->next)
		temp_token = temp_token->next;
	temp_token->next = new_token;
}

char	*get_redir_token_value(char *cmd_str, int *i)
{
	char	*tok_val;

	tok_val = NULL;
	if (cmd_str[*i] == '<' && cmd_str[*i + 1] == '<')
		tok_val = ft_strdup("<<");
	else if (cmd_str[*i] == '<')
		tok_val = ft_strdup("<");
	else if (cmd_str[*i] == '>' && cmd_str[*i + 1] == '>')
		tok_val = ft_strdup(">>");
	else if (cmd_str[*i] == '>')
		tok_val = ft_strdup(">");
	if (!tok_val)
		return (NULL);
	if (ft_strcmp(tok_val, "<") == 0 || ft_strcmp(tok_val, ">") == 0)
		(*i)++;
	else if (ft_strcmp(tok_val, "<<") == 0 || ft_strcmp(tok_val, ">>") == 0)
		(*i) = *i + 2;
	return (tok_val);
}
