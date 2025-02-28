#include "minishell.h"

static void 	print_env(t_env *env)
{
	int 	i;

	i = -1;
	while (env[++i].key != NULL)
	{
		if (env[i].value != NULL)
		{
			if (env[i].key && (env)[i].key[0] != '\0')
			{
				ft_putstr_fd(env[i].key, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
			}
			ft_putendl_fd(env[i].value, STDOUT_FILENO);
		}
	}
}
int		ft_env(t_mshell *mshell, char **args)
{
	int 	error_code;

	error_code = 0;
	if (args[1])
	{
		ft_putstr_fd("env: `", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd("`: No such file or directory", STDERR_FILENO);
		error_code = 127;
	}
	else
		print_env(mshell->env);
	mshell->exit_code = error_code;
	return (error_code);
}