#include "minishell.h"

void	minishell(t_mshell *mshell)
{
	char	*input_str;

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
			cleanup_on_loop(mshell);
		}
	}
	rl_clear_history();
}


// void	minishell(t_mshell *mshell)
// {
// 	char	*input_str;
// //	printf("inside mini init\n");
// 	while (1) // need signal handle for exit
// 	{
// 		//printf("inside mini init loop\n");
// 		input_str = readline(PROMPT);
// 		if (!input_str)
// 		{
// 			printf("no input\n");
// 			break;
// 		}
// 		if (strcmp(input_str, ""))
// 		{
// 			add_history(input_str);
// 			if (parse_input(mshell, input_str))
// 			{
// 				free(input_str);
// 				continue ;
// 			}
// 			free(input_str);
// 			builtins_execv(mshell);
// 			cleanup_on_loop(mshell);
// 			// execute_mshell(mshell);
// 			// clean_mshell(mshell);
// 		}
// 		//free(input_str); // else where input need to free??
// 	}
// 	rl_clear_history();
// 	return ;
// }