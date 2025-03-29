#include "minishell.h"

static int	mshell_data_init(t_mshell *mshell, char **envp)
{
	mshell->env = init_env(envp);
	if (!mshell->env)
		return (1);
	mshell->count_cmds = 0;
	mshell->cmds = NULL;
	mshell->pipe_fd[0] = -1;
	mshell->pipe_fd[1] = -1;
	mshell->prev_read_fd = STDIN_FILENO;
	mshell->p_id = NULL;
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
	if (mshell_data_init(&mshell, envp))
		exit(EXIT_FAILURE);
	minishell(&mshell);
	cleanup_mshell(&mshell);
	exit(mshell.exit_code);
}

// bash -c "$(curl -fsSL https://raw.githubusercontent.com/zstenger93/42_minishell_tester/master/install.sh)"
