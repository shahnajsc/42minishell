
#include "minishell.h"

int	parse_input(t_mshell *mshell, char *input_str)
{
	if (!input_str)
		return (EXIT_FAILURE);
	if (input_str && !*input_str)
		return (EXIT_SUCCESS);
	if (pre_validation_input(mshell, input_str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (tokenize_input(mshell, input_str))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
