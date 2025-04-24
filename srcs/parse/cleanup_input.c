/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:52:26 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/06 16:38:17 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirects(t_redirect *redirects, t_token *token)
{
	int	len;
	int	i;

	if (!redirects || !token)
		return ;
	i = 0;
	len = get_rd_list_len(token);
	while (i < len)
	{
		if (redirects[i].file_deli)
		{
			free(redirects[i].file_deli);
			redirects[i].file_deli = NULL;
		}
		if (redirects[i].hd_lines)
		{
			free(redirects[i].hd_lines);
			redirects[i].hd_lines = NULL;
		}
		i++;
	}
	free(redirects);
	redirects = NULL;
}

static void	free_tokens(t_token *token)
{
	t_token	*cur_token;
	t_token	*temp;

	if (!token)
		return ;
	cur_token = token;
	while (cur_token)
	{
		temp = cur_token;
		if (temp->tok_value)
		{
			free(temp->tok_value);
			temp->tok_value = NULL;
		}
		cur_token = cur_token->next;
		free(temp);
	}
	token = NULL;
}

static void	close_free_pipe(t_mshell *mshell)
{
	if (!mshell)
		return ;
	if (mshell->pipe_fd[0] >= 0)
		close(mshell->pipe_fd[0]);
	if (mshell->pipe_fd[1] >= 0)
		close(mshell->pipe_fd[1]);
	if (mshell->p_id)
	{
		free(mshell->p_id);
		mshell->p_id = NULL;
	}
}

static void	close_cmd_fds(t_cmd *cmd)
{
	if (cmd->std_fd[0] > -1)
		close(cmd->std_fd[0]);
	if (cmd->std_fd[1] > -1)
		close(cmd->std_fd[1]);
	if (cmd->redi_fd[0] > -1)
		close(cmd->redi_fd[0]);
	if (cmd->redi_fd[1] > -1)
		close(cmd->redi_fd[1]);
}

void	cleanup_on_loop(t_mshell *mshell)
{
	int	i;

	if (!mshell || !mshell->cmds)
		return ;
	i = 0;
	while (i < mshell->count_cmds)
	{
		clean_free_str(mshell->cmds[i].cmd_str);
		clean_free_str(mshell->cmds[i].cmd_name);
		ft_free_grid((void **)mshell->cmds[i].splitted_cmd);
		free_redirects(mshell->cmds[i].redirects, mshell->cmds[i].token);
		free_tokens(mshell->cmds[i].token);
		close_cmd_fds(&mshell->cmds[i]);
		i++;
	}
	free(mshell->cmds);
	mshell->cmds = NULL;
	close_free_pipe(mshell);
	mshell->count_cmds = 0;
}
