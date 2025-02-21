#include "minishell.h"

static void	init_cmds(t_mshell*mshell, char *input_str)
{
	char	**cmds_temp;
	int	i;

	i = 0;
	printf("token function begin \n");
	cmds_temp = split_input_by_pipes(mshell->count_cmds, input_str);
	if (!cmds_temp)
	{
		printf("no splitted cmds token function\n");
		return ;
	}
	// while (cmds_temp[i])
	// {
	// 	printf("a[%d] : value[%s]\n", i, cmds_temp[i]);
	// 	i++;
	// }
	// printf("\n");
	// if (!cmds_temp)
	// 	return ;
	while (i < mshell->count_cmds + 1)
	{
		printf("ms[%d] : value[%s]\n", i, cmds_temp[i]);
		mshell->cmds[i].cmd = cmds_temp[i];
		mshell->cmds[i].in_fd= -1;
		mshell->cmds[i].out_fd= -1;
		mshell->cmds[i].splitted_cmd = NULL; //make splitted cmd
		mshell->cmds[i].token = NULL; // make token
		i++;
	}
}

static int	update_mshell(t_mshell*mshell, char *input_str)
{
	if (!mshell)
		return (1);
	mshell->count_cmds = count_pipes(input_str);
	mshell->cmds = (t_cmd *)ft_calloc(mshell->count_cmds, sizeof(t_cmd));
	if  (!mshell->cmds)
		return (1);
	// mshell->cmds->token = (t_token *)ft_calloc(mshell->token_list->total_token, sizeof(t_token));
	// if (!mshell->token_list->token)
	// 	return (1);
	init_cmds(mshell, input_str);
	return (0);
}

int	tokenize_input(t_mshell *mshell, char *input_str)
{
	if (!mshell || !input_str || !*input_str)
		return (syntax_pre_error(mshell, ERR_COMN, "Failed: tokenize_init()_1")); //check for actual  bash error code
	if (update_mshell(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Failed: tokenize_init()_2")); //check for actual  bash error code
	//printf("id[%d] : value[%s]\n", 1, mshell->cmds[0].cmd);
	//int i = 0;
	// while (mshell->cmds->cmd)
	// {
	// 	printf("id[%d] : value[%s]\n", 1, mshell->cmds[0].cmd);
	// 	//i++;
	// }
	return (0);
}
