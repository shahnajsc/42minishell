#include "minishell.h"


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char  *input;

	while (1)
	{
		input = readline("minishell% ");
		if (!input)
			break;
		if (ft_strcmp(input, "env") == 0)
			ft_env(env);
		if (ft_strcmp(input, "pwd") == 0)
			ft_pwd();
		add_history(input);
		free(input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}