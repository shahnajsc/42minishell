#include "minishell.h"

int execute_builtins(t_mshell *mshell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_name, "env") == 0)
		return (ft_env(mshell, cmd->splitted_cmd));
	else if (ft_strcmp(cmd->cmd_name,  "pwd") == 0)
		return (ft_pwd(mshell));
	else if (ft_strcmp(cmd->cmd_name,  "export") == 0)
		return (ft_export(mshell, cmd->splitted_cmd));
	else if (ft_strcmp(cmd->cmd_name,  "cd") == 0)
		return (ft_cd(mshell, cmd->splitted_cmd));
	else if (ft_strcmp(cmd->cmd_name,  "echo") == 0)
		return (ft_echo(mshell, cmd->splitted_cmd));
	else if (ft_strcmp(cmd->cmd_name,  "exit") == 0)
		return (ft_exit(mshell, cmd->splitted_cmd));
	else if (ft_strcmp(cmd->cmd_name,  "unset") == 0)
		return (ft_unset(mshell, cmd->splitted_cmd, 1, 0));
	return (EXIT_SUCCESS);
}
