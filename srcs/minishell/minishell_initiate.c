#include "minishell.h"

///.......FOR TESTER....////

// int	minishell(t_mshell *mshell)
// {
// 	char	*input_str;
// 	setup_signal_handlers();
// 	while (1) // need signal handle for exit
// 	{
// 		if (isatty(fileno(stdin)))
// 			input_str = readline(PROMPT);
// 		else
// 		{
// 			char	*line;
// 			line = get_next_line(fileno(stdin));
// 			input_str = ft_strtrim(line, "\n");
// 			free(line);
// 		}
// 		if (!input_str)
// 			break ;
// 		else
// 		{
// 			add_history(input_str);
// 			if (parse_input(mshell, input_str))
// 			{
// 				free(input_str);
// 				continue ;
// 			}
// 			free(input_str);
// 			if (mshell->cmds)
// 				handle_command_execution(mshell);
// 			cleanup_on_loop(mshell);
// 		}
// 	}
// 	rl_clear_history();
// 	return (mshell->exit_code);
// }

//.......MAIN FUNCTION....///

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
				execute_cmds(mshell);
			//printf("before mini: %d\n", mshell->exit_code);
			cleanup_on_loop(mshell);
			//printf("after mini: %d\n", mshell->exit_code);
		}
	}
	rl_clear_history();
	return (mshell->exit_code);
}
