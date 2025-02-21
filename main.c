#include "minishell.h"

static int mshell_data_init(t_mshell *mshell, char **envp)
{
	ft_memset(mshell, 0, sizeof(mshell));
	mshell->envp = envp_duplicate(envp);
	if (!mshell->envp)
		return (1); // error msg
	mshell->count_cmds = 0;
	mshell->cmds = NULL;
	mshell->exit_code = 0;
	return (0);
}



int	main(int argc, char **argv, char **envp)
{
	t_mshell mshell;

	if (argc != 1)
	{
		ft_putstr_fd("Error: Correct  argument: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
	(void)argv;
	if (mshell_data_init(&mshell, envp))
		exit(EXIT_FAILURE);
	minishell(&mshell);
}
