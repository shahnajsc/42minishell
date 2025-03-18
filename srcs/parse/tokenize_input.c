#include "minishell.h"

static int	init_cmds(t_mshell*mshell, char *input_str)
{
	char	**cmds_temp;
	int		i;

	i = 0;
	cmds_temp = split_input_by_pipes(mshell->count_cmds, input_str);
	if (!cmds_temp)
	{
		printf("no splitted cmds token function\n");
		return (1);
	}
	while (cmds_temp[i])
	{
		mshell->cmds[i].token = NULL; // make token
		mshell->cmds[i].redirects = NULL;
		mshell->cmds[i].is_here_exp = 0;
		mshell->cmds[i].cmd_str = ft_strdup(cmds_temp[i]);
		mshell->cmds[i].cmd_name = NULL;
		mshell->cmds[i].splitted_cmd = NULL;
		// mshell->cmds[i].in_fd = -1;
		// mshell->cmds[i].out_fd = -1;
		i++;
	}
	ft_free_grid((void **)cmds_temp);
	return (0);
}

static int	update_mshell(t_mshell*mshell, char *input_str)
{
	if (!mshell)
		return (1);
	mshell->count_cmds = count_pipes(input_str) + 1;
	mshell->cmds = (t_cmd *)ft_calloc(mshell->count_cmds, sizeof(t_cmd));
	if (!mshell->cmds)
		return (1);
	return (0);
}

int	tokenize_input(t_mshell *mshell, char *input_str)
{
	int	i;

	i = 0;
	if (!mshell || !input_str || !*input_str)
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed: NULL input")); //check for actual  bash error code
	if (update_mshell(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed: mshell  update")); //check for actual  bash error code
	if (init_cmds(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed: Struct t_cmd init"));
	while (i < mshell->count_cmds)
	{
		mshell->cmds[i].token = create_tokens_list(mshell, mshell->cmds[i].cmd_str, i);
		if (!mshell->cmds[i].token)
		{
			//printf("no token %d\n", mshell->count_cmds);
			return (1);
		}

		mshell->cmds[i].splitted_cmd = splitted_cmd(mshell, i);
		if (!mshell->cmds[i].splitted_cmd)
		{
			//printf("no cmd %d\n", mshell->count_cmds);
			return (1);
		}
		mshell->cmds[i].redirects = create_redirects_list(mshell, i);
		if (!mshell->cmds[i].redirects && get_rd_list_len(mshell->cmds[i].token) > 0)
			return (1);
		i++;
	}
	//print_command_list(mshell);
	return (0);
}

	//...................
	// int k = 0;
	// while (k < mshell->count_cmds)
	// {
	// 	printf("id[%d] : value[%s]\n", k, mshell->cmds[k].cmd_str);
	// 	k++;
	// }
	// printf("\n");
	//...................

//................................
	// printf("full str:[%s]\n", input_str);
	// int k = 0;
	// while (cmds_temp[k] != NULL)
	// {
	// 	printf("b[%d] : value[%s]\n", k, cmds_temp[k]);
	// 	k++;
	// }
	// printf("\n");

	//................................
		//printf("id[%d] : value[%s]\n", 1, mshell->cmds[0].cmd);
	// int i = 0;
	// while (i < mshell->count_cmds)
	// {
	// 	printf("id[%d] : value[%s]\n", 1, mshell->cmds[i].cmd);
	// 	i++;
	// }

		//printf("inside struct:[%d] : value[%s] ", i, mshell->cmds[i].cmd);
		// printf("in_id:[%d]", mshell->cmds[i].in_fd);
		// printf("out_id:[%d]\n", mshell->cmds[i].out_fd);

	// int k = 0;
	// //int m = 0;
	// while (mshell->cmds[i].splitted_cmd[k] != NULL)
	// {
	// 	printf("cmd[%d] sp[%d] : value[%s]\n", i, k, mshell->cmds[i].splitted_cmd[k]);
	// 	k++;
	// }
	// printf("\n");
