#include "minishell.h"

int	check_is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_name, "env") == 0
		|| ft_strcmp(cmd->cmd_name, "pwd") == 0
		|| ft_strcmp(cmd->cmd_name, "export") == 0
		|| ft_strcmp(cmd->cmd_name, "cd") == 0
		|| ft_strcmp(cmd->cmd_name, "echo") == 0
		|| ft_strcmp(cmd->cmd_name, "exit") == 0
		|| ft_strcmp(cmd->cmd_name, "unset") == 0)
		return (1);
	return (0);
}

// static int	assign_pipe_fds(t_mshell *mshell, int **fds, int cmd_count, int i)
// {
// 	if (!mshell || !fds)
// 		return (1);
// 	if (pipe(fds[i]) == -1)
// 		return (1);
// 	if (i == 0)
// 		mshell->cmds[i].in_fd = STDIN_FILENO;
// 	else
// 		mshell->cmds[i].in_fd = fds[i - 1][0];
// 	if (i == (cmd_count - 1))
// 		mshell->cmds[i].out_fd = STDOUT_FILENO;
// 	else
// 		mshell->cmds[i].out_fd = fds[i][1];
// 	return (0);
// }

// static int	init_pipe(t_mshell *mshell, int cmd_count)
// {
// 	int	**fds;
// 	int	i;

// 	i = -1;
// 	fds = (int **)malloc((cmd_count) * sizeof(int *));
// 	if (!fds)
// 		return (1);
// 	while (fds && ++i < (cmd_count - 1))
// 	{
// 		fds[i] = (int *)malloc(2 * sizeof(int));
// 		if (!fds[i])
// 		{
// 			ft_free_grid((void **)fds);
// 			return (1);
// 		}
// 		if (assign_pipe_fds(mshell, fds, cmd_count, i))
// 			return (ft_free_grid((void **)fds), 1);
// 	}
// 	fds[i] = NULL;
// 	mshell->pipe_fds = fds;
// 	return (0);
// }
// void	reset_close_fds(t_cmd)
// {

// }

void	builtins_in_parent(t_mshell *mshell, t_cmd *cmd)
{
	//int	temp_fds[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
	int len;

	len = get_rd_list_len(cmd->token);
	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
	{
		// redirect_fd(temp_fds[0], STDIN_FILENO);
		// redirect_fd(temp_fds[1], STDOUT_FILENO);
		return ;
	}
	if (execute_builtins(mshell, cmd) > 0 )
	{
		//reset_close_fds(cmd);
		// redirect_fd(temp_fds[0], STDIN_FILENO);
		// redirect_fd(temp_fds[1], STDOUT_FILENO);
		return;
	}
	// redirect_fd(temp_fds[0], STDIN_FILENO);
	// redirect_fd(temp_fds[1], STDOUT_FILENO);


}
// echo hi >> out > outfile


void	execute_cmds(t_mshell *mshell)
{
	int	i;

	if (!mshell->cmds || mshell->count_cmds == 0)
		return ;
	i = 0;
	// if (mshell->count_cmds > 1)
	// {
	// 	if (init_pipe(mshell, mshell->count_cmds))
	// 		return ;
	// 	printf("fd: %d, %d\n", mshell->pipe_fds[1][0], mshell->pipe_fds[1][1]);
	// }
	if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
	{
		builtins_in_parent(mshell, &mshell->cmds[0]);
	}
	else
	{
		printf("external CMD\n");
		// while (i < mshell->count_cmds)
		// {
		// 	// create pipe
		// 	// skip rd
		// 	// call execution: bulit/external
		// 	//builtin : cleaning
		// 	// extranal

		// 	// if (check_is_builtin(&mshell->cmds[i]))
		// 	// 	execute_builtins(mshell, &mshell->cmds[i]);
		// 	// else
		// 	// 	printf("external CMD\n");
		// 	i++;
		// }
	}
}
