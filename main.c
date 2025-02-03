#include "./minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>

int	main(void)
{

	char *input;

	while (1)
	{
		input = readline("minishell% ");
		if (input == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*input)
		{
			add_history(input);
			printf("You entered: %s\n", input);
		}
	}
	// rl_clear_history();
	free(input);
	return (EXIT_SUCCESS);
}
