#include "minishell.h"

int	minishell(t_mshell *mshell)
{
	char	*input_str;

	// int status = 0;
	setup_signal_handlers();
	while (1) // need signal handle for exit
	{
		input_str = readline(PROMPT);
		if (!input_str)
			break ;
		else
		{
			add_history(input_str);
			if (parse_input(mshell, input_str))
			{
				free(input_str);
				continue ;
			}
			free(input_str);
			if (mshell->cmds)
				handle_command_execution(mshell);
			cleanup_on_loop(mshell);
		}
	}
	rl_clear_history();
	return (mshell->exit_code);
}
