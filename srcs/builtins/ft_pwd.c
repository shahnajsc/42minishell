#include "minishell.h"

int	ft_pwd(t_mshell *mshell)
{
	char 		*cwd;
	t_env 		*pwd;

	if (!mshell || !mshell->env)
		return (0);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{	
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
	}
	else
	{
		pwd = get_env_var(mshell->env, "PWD");
		if (!pwd || !pwd->value)
			return (1);
		cwd = pwd->value;
		ft_putendl_fd(cwd, STDOUT_FILENO);
	}
	return (0);
}
