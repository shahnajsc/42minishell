
#include "minishell.h"

int	parse_input(t_mshell *mshell, char *input_str)
{
	if (!input_str)
		return (1);
	if (input_pre_validation(mshell, input_str))
		return (1);
	if (tokenize_input(mshell, input_str))
	{
		//printf("in count %d\n", mshell->count_cmds);
		return (1);
	}
	return (0);
}
