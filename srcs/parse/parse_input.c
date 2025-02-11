#include "minishell.h"

void	parse_input(t_mshell *mshell, char *input_str)
{
	if (!input_str)
		return ;
	if (input_pre_validation(input_str))
		return ;
	tokenize_input(mshell, input_str);
}
