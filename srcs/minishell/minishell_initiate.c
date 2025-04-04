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
// 		{
// 			ft_putstr_fd("exit\n", STDOUT_FILENO);
// 			break ;
// 		}

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
// 				execute_cmds(mshell);
// 			cleanup_on_loop(mshell);
// 		}
// 	}
// 	rl_clear_history();
// 	return (mshell->exit_code);
// }

//.......MAIN FUNCTION....///
static void interrupt_input(t_mshell *mshell)
{
	if (g_heredoc == SIGINT)
	{
		g_heredoc = 0;
		mshell->exit_code = 130;
	}
}
void handle_all(t_mshell *mshell, char *line)
{
	add_history(line);
	if (mshell->cmds)
		execute_cmds(mshell);
	cleanup_on_loop(mshell);
}

int	minishell(t_mshell *mshell)
{
	char	*input_str;

	setup_signal_handlers();
	while (1)
	{
		g_heredoc = 0;
		input_str = readline(PROMPT);
		if (!input_str)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		interrupt_input(mshell);
		if (parse_input(mshell, input_str))
		{
			free(input_str);
			continue ;
		}
		add_history(input_str);
		if (mshell->cmds)
			execute_cmds(mshell);
		cleanup_on_loop(mshell);
		// handle_all(mshell, input_str);
	}
	rl_clear_history();
	return (mshell->exit_code);
}
