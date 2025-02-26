#include "minishell.h"

// static t_token	init_token(t_mshell *mshell, t_cmd *cmd_ptr)
// {
// 	mshell->cmds->token = (t_token *)ft_calloc(2, sizeof(t_token));
// 	if (!mshell->cmds->token)
// 		return (NULL);
// }

static int	init_cmds(t_mshell*mshell, char *input_str)
{
	char	**cmds_temp;
	int	i;

	i = 0;
	cmds_temp = split_input_by_pipes(mshell->count_cmds, input_str);
	if (!cmds_temp)
	{
		printf("no splitted cmds token function\n");
		return (1);
	}
	while (cmds_temp[i])
	{
		mshell->cmds[i].cmd_str = cmds_temp[i];
		mshell->cmds[i].in_fd= -1;
		mshell->cmds[i].out_fd= -1;
		mshell->cmds[i].splitted_cmd = NULL;
		mshell->cmds[i].token = NULL; // make token
		i++;
	}
	free(cmds_temp);
	printf("\n");
	return (0);
}

t_token	*create_tokens_list(t_mshell *mshell, int index)
{
	t_token	*head_token;
	t_token	*new_token;
	char *cmd_str;
	t_token_type tok_type;
	int	i;

	i = 0;
	printf("inside token creation function\n");
	cmd_str = mshell->cmds[index].cmd_str;
	printf("cmd str[%d]:[%s]\n", index, cmd_str);
	head_token = NULL;
	while (cmd_str[i])
	{
		printf(" loop inside token creation function\n");
		tok_type = get_token_type(cmd_str, i);
		printf("tok_type :%u\n", tok_type);
		if (tok_type == CMD)
			new_token = create_cmd_token(cmd_str, &i, tok_type);
		else
			new_token = create_other_token(&i, tok_type);
		if (!new_token)
			return (NULL); // free the whole token list
		add_new_token(&head_token, new_token);
	}
	return (head_token);
}

static int	update_mshell(t_mshell*mshell, char *input_str)
{
	if (!mshell)
		return (1);
	mshell->count_cmds = count_pipes(input_str) + 1;
	mshell->cmds = (t_cmd *)ft_calloc(mshell->count_cmds, sizeof(t_cmd));
	if  (!mshell->cmds)
		return (1);
	return (0);
}

int	tokenize_input(t_mshell *mshell, char *input_str)
{
	int	index;

	index = 0;
	if (!mshell || !input_str || !*input_str)
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed: NULL input")); //check for actual  bash error code
	if (update_mshell(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed: mshell  update")); //check for actual  bash error code
	if (init_cmds(mshell, input_str))
		return (syntax_pre_error(mshell, ERR_COMN, "Tokenization failed: Struct t_cmd init"));
	//...................
	int k = 0;
	while (k < mshell->count_cmds)
	{
		printf("id[%d] : value[%s]\n", k, mshell->cmds[k].cmd_str);
		k++;
	}
	printf("\n");
	//...................
	while (index < mshell->count_cmds)
	{
		printf("inside main token function\n");
		mshell->cmds[index].token = create_tokens_list(mshell, index);
		if (!mshell->cmds[index].token)
		{
			printf("no token\n");
			//return (1); // free already created token
		}
		printf("token id [%d]\n", index);
		index++;
	}
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
