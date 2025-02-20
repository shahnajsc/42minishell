#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	t_env 	*env;
	char  *input;

	(void)argc;
	(void)argv;
	duplicate_env(envp, &env);

	while (1)
	{
		input = readline("minishell@42% ");
		// printf("%s\n", input);
		char **split = ft_split(input, ' ');
		char *cmd = split[0];
		if (!input)
			break;
		if (ft_strcmp(input, "env") == 0)
			ft_env(env);
		else if (ft_strcmp(input, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd, "export") == 0)
		{
			if (split[1])
				export_var(&env, split[1]);
			else
				ft_export(env);
		}
		else if (ft_strcmp(cmd, "cd") == 0)
			ft_cd(&env, split[1]);
		else if (ft_strcmp(cmd, "echo") == 0)
			ft_echo(&env, split[1]);
		else if (ft_strcmp(cmd, "unset") == 0)
			ft_unset(&env, split[1]);
		add_history(input);
		free(input);
	}
	rl_clear_history();
	free_env(env, env_size(envp));
	return (EXIT_SUCCESS);
}
// int main(int argc, char **argv)
// {
// 	char	*input_str;

// 	(void)argc;
// 	(void)argv;
// 	while (1) // need signal handle for exit
// 	{
// 		input_str = readline(PROMPT);
// 		if (!input_str)
// 		{
// 			printf("no input\n");
// 			break;
// 		}
// 		add_history(input_str);
// 		free(input_str);
// 	}
// 	if (input_str)
// 	rl_clear_history();
// 	return (EXIT_SUCCESS);
// }