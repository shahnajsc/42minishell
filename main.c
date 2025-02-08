#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	t_env 	env;
	char  *input;

	(void)argc;
	(void)argv;

	while (1)
	{
		input = readline("minishell@42% ");
		char **split = ft_split(input, ' ');
		char *cmd = split[0];
		if (!input)
			break;
		if (ft_strcmp(input, "env") == 0)
			ft_env(envp, &env);
		else if (ft_strcmp(input, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd, "export") == 0)
			ft_export(&env, envp, split[1]);
		add_history(input);
		free(input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}