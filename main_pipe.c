#include "../includes/minishell.h"

static int mshell_data_init(t_mshell *mshell, char **envp)
{
	ft_memset(mshell, 0, sizeof(mshell));
	mshell->envp = envp_duplicate(envp);
	if (!mshell->envp)
		return (1);
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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	data;
// 	int		pipe_status;

// 	pipe_status = 0;
// 	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
// 	{
// 		ft_putstr_fd("Correct  arguments: infile cmd1..cmd(n) outfile\n", 2);
// 		exit(1);
// 	}
// 	data_init(&data, argc, argv, envp);
// 	pipe_status = pipex(&data);
// 	clean_at_exit(&data);
// 	exit(pipe_status);
// }
