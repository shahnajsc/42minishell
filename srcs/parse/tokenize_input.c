/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:54:15 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 16:43:21 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmds(t_mshell *mshell, char *input_str, int i)
{
	char	**cmds_temp;

	cmds_temp = split_input_by_pipes(mshell->count_cmds, input_str);
	if (!cmds_temp)
		return (EXIT_FAILURE);
	while (cmds_temp[++i])
	{
		mshell->cmds[i].token = NULL;
		mshell->cmds[i].redirects = NULL;
		mshell->cmds[i].is_hd_quote = 0;
		mshell->cmds[i].cmd_str = ft_strdup(cmds_temp[i]);
		if (!mshell->cmds[i].cmd_str)
		{
			ft_free_grid((void **)cmds_temp);
			return (EXIT_FAILURE);
		}
		mshell->cmds[i].cmd_name = NULL;
		mshell->cmds[i].splitted_cmd = NULL;
		mshell->cmds[i].std_fd[0] = -1;
		mshell->cmds[i].std_fd[1] = -1;
		mshell->cmds[i].redi_fd[0] = -2;
		mshell->cmds[i].redi_fd[1] = -2;
	}
	ft_free_grid((void **)cmds_temp);
	return (EXIT_SUCCESS);
}

static int	update_mshell(t_mshell *mshell, char *input_str)
{
	if (!mshell)
		return (EXIT_FAILURE);
	mshell->count_cmds = count_pipes(input_str) + 1;
	mshell->cmds = (t_cmd *)ft_calloc(mshell->count_cmds, sizeof(t_cmd));
	if (!mshell->cmds)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	tokenize_input(t_mshell *mshell, char *input_str)
{
	int	i;

	i = 0;
	if (!mshell || !input_str || !*input_str)
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed"));
	if (update_mshell(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed"));
	if (init_cmds(mshell, input_str, -1))
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed"));
	while (i < mshell->count_cmds)
	{
		mshell->cmds[i].token = create_tokens_list(mshell,
				mshell->cmds[i].cmd_str, i);
		mshell->cmds[i].splitted_cmd = splitted_cmd(mshell, i);
		mshell->cmds[i].redirects = create_redirects_list(mshell, i);
		if (!mshell->cmds[i].redirects
			&& get_rd_list_len(mshell->cmds[i].token) > 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
