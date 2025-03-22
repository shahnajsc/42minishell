#include "minishell.h"

int execute_builtins(t_mshell *mshell, t_cmd *cmd)
{
	int 	status;

	status = 0;
	if (ft_strcmp(cmd->cmd_name, "env") == 0)
		status = ft_env(mshell, cmd->splitted_cmd);
	else if (ft_strcmp(cmd->cmd_name,  "pwd") == 0)
		status = ft_pwd(mshell);
	else if (ft_strcmp(cmd->cmd_name,  "export") == 0)
		status = ft_export(mshell, cmd->splitted_cmd);
	else if (ft_strcmp(cmd->cmd_name,  "cd") == 0)
		status = ft_cd(mshell, cmd->splitted_cmd);
	else if (ft_strcmp(cmd->cmd_name,  "echo") == 0)
		status = ft_echo(mshell, cmd->splitted_cmd);
	else if (ft_strcmp(cmd->cmd_name,  "exit") == 0)
		status = ft_exit(mshell, cmd->splitted_cmd);
	else if (ft_strcmp(cmd->cmd_name,  "unset") == 0)
		status = ft_unset(mshell, cmd->splitted_cmd, 1, 0);
	mshell->exit_code = status;
	return (status);
}
