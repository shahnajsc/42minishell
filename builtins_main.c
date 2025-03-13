// #include "minishell.h"

// static int mshell_data_init(t_mshell *mshell, char **envp)
// {
// 	ft_memset(mshell, 0, sizeof(mshell));
// 	mshell->env = init_env(envp); //change your one
// 	if (!mshell->env)
// 		return (1);
// 	mshell->b_state = init_built_state();
// 	if (!mshell->b_state)
// 		return (1);
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_mshell mshell;

// 	(void)argv;
// 	if (argc != 1)
// 	{
// 		ft_putstr_fd("Error: Correct  argument: ./minishell\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (mshell_data_init(&mshell, envp))
// 		exit(EXIT_FAILURE);
// 	minishell(&mshell);
// }
