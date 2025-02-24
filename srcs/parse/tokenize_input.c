#include "minishell.h"

// static t_token	init_token(t_mshell *mshell, t_cmd *cmd_ptr)
// {
// 	mshell->cmds->token = (t_token *)ft_calloc(2, sizeof(t_token));
// 	if (!mshell->cmds->token)
// 		return (NULL);
// }

static void	init_cmds(t_mshell*mshell, char *input_str)
{
	char	**cmds_temp;
	int	i;

	i = 0;
	cmds_temp = split_input_by_pipes(mshell->count_cmds, input_str);
	if (!cmds_temp)
	{
		printf("no splitted cmds token function\n");
		return ;
	}
	while (cmds_temp[i])
	{
		mshell->cmds[i].cmd = cmds_temp[i];
		mshell->cmds[i].in_fd= -1;
		mshell->cmds[i].out_fd= -1;
		mshell->cmds[i].splitted_cmd = ft_split(mshell->cmds[i].cmd, ' '); //make splitted cmd
		if (!mshell->cmds[i].splitted_cmd)
			return ;
		mshell->cmds[i].token = NULL; // make token
		i++;
	}
	printf("\n");
}

static int	update_mshell(t_mshell*mshell, char *input_str)
{
	if (!mshell)
		return (1);
	mshell->count_cmds = count_pipes(input_str) + 1;
	mshell->cmds = (t_cmd *)ft_calloc(mshell->count_cmds, sizeof(t_cmd));
	if  (!mshell->cmds)
		return (1);
	init_cmds(mshell, input_str);
	return (0);
}

int	tokenize_input(t_mshell *mshell, char *input_str)
{
	if (!mshell || !input_str || !*input_str)
		return (syntax_pre_error(mshell, ERR_COMN, "Failed: tokenize_init()_1")); //check for actual  bash error code
	if (update_mshell(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Failed: tokenize_init()_2")); //check for actual  bash error code
	return (0);
}
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
