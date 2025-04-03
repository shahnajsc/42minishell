/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitted_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:53:15 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 09:40:40 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_splitted_cmd_len(t_token *token_list)
{
	int		len;
	t_token	*current_token;

	len = 0;
	current_token = token_list;
	while (current_token)
	{
		if (current_token->tok_type == CMD && current_token->tok_value)
			len++;
		current_token = current_token->next;
	}
	return (len);
}

static char	**create_splitted_cmd(char **splitted_cmd, t_token *token_list)
{
	t_token	*current_token;
	int		i;

	i = 0;
	if (!splitted_cmd)
		return (NULL);
	current_token = token_list;
	while (current_token)
	{
		if (current_token->tok_type == CMD && current_token->tok_value)
		{
			splitted_cmd[i] = ft_strdup(current_token->tok_value);
			if (!splitted_cmd[i])
			{
				while (i > 0)
					free(splitted_cmd[--i]);
				free(splitted_cmd);
			}
			i++;
		}
		current_token = current_token->next;
	}
	splitted_cmd[i] = NULL;
	// if (splitted_cmd[0] == NULL)
	// {
	// 	ft_free_grid((void **)splitted_cmd);
	// 	return (NULL);
	// }
	return (splitted_cmd);
}

char	**splitted_cmd(t_mshell *mshell, int i)
{
	int		len;
	char	**splitted_cmd;
	t_token	*token_list;

	token_list = mshell->cmds[i].token;
	if (!token_list)
		return (NULL);
	len = get_splitted_cmd_len(token_list);
	splitted_cmd = ft_calloc((len + 1), sizeof(char *));
	if (!splitted_cmd)
		return (NULL);
	splitted_cmd = create_splitted_cmd(splitted_cmd, token_list);
	if (!splitted_cmd || !splitted_cmd[0]) // check
	{
		ft_free_grid((void **)splitted_cmd);
		return (NULL);
	}
	mshell->cmds[i].cmd_name = ft_strdup(splitted_cmd[0]);
	if (!mshell->cmds[i].cmd_name)
		return (NULL);
	return (splitted_cmd);
}
