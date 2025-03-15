#include "minishell.h"

int builtins_execv(t_mshell *mshell)
{
	if (ft_strcmp(mshell->cmds[0].cmd_name, "env") == 0)
		return (ft_env(mshell, mshell->cmds[0].splitted_cmd));
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "pwd") == 0)
		return (ft_pwd(mshell));
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "export") == 0)
		return (ft_export(mshell, mshell->cmds[0].splitted_cmd));
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "cd") == 0)
		return (ft_cd(mshell, mshell->cmds[0].splitted_cmd));
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "echo") == 0)
		return (ft_echo(mshell, mshell->cmds[0].splitted_cmd));
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "exit") == 0)
		return (ft_exit(mshell, mshell->cmds[0].splitted_cmd));
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "unset") == 0)
		return (ft_unset(mshell, mshell->cmds[0].splitted_cmd, 0, 0));
	return (EXIT_SUCCESS);
}
