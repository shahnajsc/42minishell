#include "minishell.h"

void	minishell(t_mshell *mshell)
{
	char	*input_str;
	// int 	status;

	setup_signal_handlers();
	while (1) // need signal handle for exit
	{
		input_str = readline(PROMPT);
		if (!input_str)
			exit_mshell(mshell);
		else
		{
			add_history(input_str);
			if (parse_input(mshell, input_str))
			{
				free(input_str);
				continue ;
			}
			free(input_str);
			builtins_execv(mshell);
			// printf("%d\n", status);
			cleanup_on_loop(mshell);
		}
	}
	rl_clear_history();
}
