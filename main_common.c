#include "./minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	char *prompt;


	(void)argc;
	(void)argv;
	prompt = NULL;
	input = readline(prompt);
	while  (1)
	{
		input = readline(prompt);
		printf("RL: %s\n", input);
		free(input);
	}
	// printf("value of ARGV[0]: %s\n", argv[0]);
	printf("value of ENVP[0]: %s\n", envp[0]);
	printf("\n");
	return (0);
}
