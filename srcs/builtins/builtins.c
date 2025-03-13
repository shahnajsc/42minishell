#include "minishell.h"

int builtins_execv(t_mshell *mshell)
{
	if (ft_strcmp(mshell->cmds[0].cmd_name, "env") == 0)
		ft_env(mshell, mshell->cmds[0].splitted_cmd);
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "pwd") == 0)
		ft_pwd(mshell);
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "export") == 0)
		ft_export(mshell, mshell->cmds[0].splitted_cmd);
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "cd") == 0)
		ft_cd(mshell, mshell->cmds[0].splitted_cmd);
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "echo") == 0)
		ft_echo(mshell, mshell->cmds[0].splitted_cmd);
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "exit") == 0)
		ft_exit(mshell, mshell->cmds[0].splitted_cmd);
	else if (ft_strcmp(mshell->cmds[0].cmd_name,  "unset") == 0)
		ft_unset(mshell, mshell->cmds[0].splitted_cmd, 1, 0);
	return (EXIT_SUCCESS);
}
