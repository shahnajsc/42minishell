#include "minishell.h"

static int	mshell_data_init(t_mshell *mshell, char **envp)
{
	mshell->env = init_env(envp);
	if (!mshell->env)
		return (1);
	//mshell->b_state = NULL;
	mshell->cmds = NULL;
	mshell->count_cmds = 0;
	mshell->p_id = NULL;
	mshell->pipe_fd[0] = -1;
	mshell->pipe_fd[1] = -1;
	mshell->prev_read_fd = STDIN_FILENO;
	mshell->exit_code = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mshell mshell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: Correct  argument: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
	//printf("inside main\n");
	if (mshell_data_init(&mshell, envp))
		exit(EXIT_FAILURE);
	//printf("after mshellll init\n");
	minishell(&mshell);
	cleanup_mshell(&mshell);
}
