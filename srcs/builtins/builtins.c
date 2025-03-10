#include "minishell.h"


int builtins_execv(t_mshell *mshell, char *input_str)
{
	char 		**args;

	args = ft_split(input_str, ' ');
	if (!args)
		return (1);
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(mshell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(mshell);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(mshell, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(mshell, args);
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(mshell, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(mshell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(mshell, args, 1, 0);
	return (EXIT_SUCCESS);
}
