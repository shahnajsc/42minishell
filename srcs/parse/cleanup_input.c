#include  "minishell.h"

static void	free_redirects(t_redirect *redirects, t_token *token)
{
	int	len;
	int	i;

	if (!redirects || !token)
		return ;
	i =  0;
	len = get_rd_list_len(token);
	while (i < len)
	{
		if (redirects[i].file_deli)
			free(redirects[i].file_deli);
		redirects[i].file_deli = NULL;
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
		free(temp->tok_value);
		temp->tok_value  = NULL;
		cur_token = cur_token->next;
		free(temp);
	}
	token = NULL;
}
void	close_free_pipe(t_mshell *mshell)
{
	int	i;

	i = 0;
	if (!mshell || !mshell->pipe_fds)
		return ;
	while (mshell->pipe_fds[i] != NULL)
	{
		if (mshell->pipe_fds[i][0] >= 0)
			close(mshell->pipe_fds[i][0]);
		if (mshell->pipe_fds[i][1] >= 0)
			close(mshell->pipe_fds[i][1]);
		free(mshell->pipe_fds[i]);
		i++;
	}
	free(mshell->pipe_fds);
	mshell->pipe_fds = NULL;
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->i_o_fd[0] > -1)
		close(cmd->i_o_fd[0]);
	if (cmd->i_o_fd[1] > -1)
		close(cmd->i_o_fd[1]);
	if (cmd->rd_fd[0] > -1)
		close(cmd->rd_fd[0]);
	if (cmd->rd_fd[1] > -1)
		close(cmd->rd_fd[1]);
}

void	cleanup_on_loop(t_mshell *mshell)
{
	int	i;
	if (!mshell || !mshell->cmds)
		return ;
	i = 0;
	while (i < mshell->count_cmds)
	{
		if (mshell->cmds[i].cmd_str)
		{
			free(mshell->cmds[i].cmd_str);
			mshell->cmds[i].cmd_str = NULL;
		}
		if (mshell->cmds[i].cmd_name)
		{
			free(mshell->cmds[i].cmd_name);
			mshell->cmds[i].cmd_name = NULL;
		}
		ft_free_grid((void **)mshell->cmds[i].splitted_cmd);
		free_redirects(mshell->cmds[i].redirects, mshell->cmds[i].token);
		free_tokens(mshell->cmds[i].token);
		close_fds(&mshell->cmds[i]);
		i++;
	}
	free(mshell->cmds);
	mshell->cmds = NULL;
	close_free_pipe(mshell);
	mshell->count_cmds = 0;
}
