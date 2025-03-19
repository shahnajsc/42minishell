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

static int	assign_pipe_fds(t_mshell *mshell, int **fds, int cmd_count, int i)
{
	if (!mshell || !fds)
		return (1);
	if (pipe(fds[i]) == -1)
		return (1);
	if (i == 0)
		mshell->cmds[i].in_fd = STDIN_FILENO;
	else
		mshell->cmds[i].in_fd = fds[i - 1][0];
	if (i == (cmd_count - 1))
		mshell->cmds[i].out_fd = STDOUT_FILENO;
	else
		mshell->cmds[i].out_fd = fds[i][1];
	return (0);
}

static int	init_pipe(t_mshell *mshell, int cmd_count)
{
	int	**fds;
	int	i;

	i = -1;
	fds = (int **)malloc((cmd_count) * sizeof(int *));
	if (!fds)
		return (1);
	while (fds && ++i < (cmd_count - 1))
	{
		fds[i] = (int *)malloc(2 * sizeof(int));
		if (!fds[i])
		{
			ft_free_grid((void **)fds);
			return (1);
		}
		if (assign_pipe_fds(mshell, fds, cmd_count, i))
			return (ft_free_grid((void **)fds), 1);
	}
	fds[i] = NULL;
	mshell->pipe_fds = fds;
	return (0);
}

void	execute_cmds(t_mshell *mshell)
{
	int	i;

	if (!mshell->cmds || mshell->count_cmds == 0)
		return ;
	i = 0;
	if (mshell->count_cmds > 1)
	{
		if (init_pipe(mshell, mshell->count_cmds))
			return ;
		printf("fd: %d, %d\n", mshell->pipe_fds[1][0], mshell->pipe_fds[1][1]);
	}
	if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
	{
		execute_builtins(mshell, &mshell->cmds[0]);
		//printf("cmdexecuted\n");
	}
	else
	{
		while (i < mshell->count_cmds)
		{
			if (check_is_builtin(&mshell->cmds[i]))
				execute_builtins(mshell, &mshell->cmds[i]);
			else
				printf("external CMD\n");
				// execute_externals(mshell, &mshell->cmds[i]);
			i++;
		}
	}
}
