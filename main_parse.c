// #include "minishell.h"


// int	minishell_ll(t_mshell *mshell)
// {
// 	char	*input_str;

// 	while (1)
// 	{
// 		input_str = readline(PROMPT);
// 		if (*input_str)
// 			add_history(input_str);
// 		if (parse_input(mshell, input_str))
// 		{
// 			free(input_str);
// 			continue ;
// 		}
// 		free(input_str);
// 	}
// 	rl_clear_history();
// 	return (0);
// }


// static int	mshell_init(t_mshell *mshell, char **envp)
// {
// 	mshell->env = init_env(envp);
// 	if (!mshell->env)
// 		return (1);
// 	mshell->count_cmds = 0;
// 	mshell->cmds = NULL;
// 	mshell->pipe_fd[0] = -1;
// 	mshell->pipe_fd[1] = -1;
// 	mshell->prev_read_fd = STDIN_FILENO;
// 	mshell->p_id = NULL;
// 	mshell->exit_code = 0;
// 	mshell->flag_path = 0;
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_mshell	mshell;

// 	(void)argv;
// 	if (argc != 1)
// 	{
// 		ft_putstr_fd("Error: Correct  argument: ./minishell\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (mshell_init(&mshell, envp))
// 		exit(EXIT_FAILURE);
// 	minishell_ll(&mshell);
// 	exit(mshell.exit_code);
// }
