#include  "minishell.h"

static void	free_redirects(t_redirect *redirects, t_token *token)
{
	int	len;
	int	i;

	if (!redirects)
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
		if (mshell->cmds[i].splitted_cmd)
			ft_free_grid((void **)mshell->cmds[i].splitted_cmd);
		if (mshell->cmds[i].redirects)
			free_redirects(mshell->cmds[i].redirects, mshell->cmds[i].token);
		if (mshell->cmds[i].token)
			free_tokens(mshell->cmds[i].token);
		i++;
	}
	free(mshell->cmds);
	mshell->cmds = NULL;
	mshell->count_cmds = 0;
}
