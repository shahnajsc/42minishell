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

void execute_cmds(t_mshell *mshell)
{
	int	i;
	int	fds[2];
	int	pipe_fd[2];

	i = 0;
	fds[0] = -2;
	fds[1] = -2;
	if (!mshell->cmds || mshell->count_cmds == 0)
		return ;
	if (check_is_builtin(mshell->cmds[0].cmd_name) && mshell->count_cmds == 1)
		execute_builtins(mshell, &mshell->cmds[0]);
	else
	{

	}


}
