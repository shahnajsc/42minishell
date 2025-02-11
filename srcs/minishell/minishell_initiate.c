#include "minishell.h"

void	minishell(t_mshell *mshell)
{
	char	*input_str;

	while (1) // need signal handle for exit
	{
		input_str = readline(PROMPT);
		if (!input_str)
		{
			printf("no input\n");
			break;
		}
		add_history(input_str);
		if (input_pre_validation(input_str))
		{
			continue ;
		}
		free(input_str);
	}
	if (input_str)
		mshell->input = input_str;
	rl_clear_history();
	return ;
}
