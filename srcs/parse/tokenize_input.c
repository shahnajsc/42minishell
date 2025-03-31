#include "minishell.h"

static int	init_cmds(t_mshell*mshell, char *input_str)
{
	char	**cmds_temp;
	int		i;

	i = 0;
	cmds_temp = split_input_by_pipes(mshell->count_cmds, input_str);
	if (!cmds_temp)
		return (EXIT_FAILURE);
	while (cmds_temp[i])
	{
		mshell->cmds[i].token = NULL; // make token
		mshell->cmds[i].redirects = NULL;
		mshell->cmds[i].is_hd_quote = 0;
		mshell->cmds[i].cmd_str = ft_strdup(cmds_temp[i]);
		if (!mshell->cmds[i].cmd_str)
			return (EXIT_FAILURE);
		mshell->cmds[i].cmd_name = NULL;
		mshell->cmds[i].splitted_cmd = NULL;
		mshell->cmds[i].std_fd[0] = -1;
		mshell->cmds[i].std_fd[1] = -1;
		mshell->cmds[i].redi_fd[0] = -2;
		mshell->cmds[i].redi_fd[1] = -2;
		i++;
	}
	ft_free_grid((void **)cmds_temp);
	return (EXIT_SUCCESS);
}

static int	update_mshell(t_mshell*mshell, char *input_str)
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
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed")); //check for actual  bash error code
	if (update_mshell(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed")); //check for actual  bash error code
	if (init_cmds(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed"));
	while (i < mshell->count_cmds)
	{
		mshell->cmds[i].token
			= create_tokens_list(mshell, mshell->cmds[i].cmd_str, i);
		if (!mshell->cmds[i].token)
			return (EXIT_FAILURE);
		mshell->cmds[i].splitted_cmd = splitted_cmd(mshell, i);
		if (!mshell->cmds[i].splitted_cmd)
			return (EXIT_FAILURE);
		mshell->cmds[i].redirects = create_redirects_list(mshell, i);
		if (!mshell->cmds[i].redirects
			&& get_rd_list_len(mshell->cmds[i].token) > 0)
			return (EXIT_FAILURE);
		i++;
	}
	//print_command_list(mshell);
	return (EXIT_SUCCESS);
}
