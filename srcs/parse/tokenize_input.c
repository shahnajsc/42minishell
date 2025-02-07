#include "minishell.h"

static int	init_tokens(t_mshell*mshell)
{
	if (!mshell)
		return (1);
	mshell->token_list = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if  (!mshell->token_list)
		return (1);
	mshell->token_list->total_token = 3;
	mshell->token_list->token = (t_token *)ft_calloc(mshell->token_list->total_token, sizeof(t_token));
	if (!mshell->token_list->token)
		return (1);
	return (0);
}

void	tokenize_input(t_mshell *mshell, char *input_str)
{
	if (!mshell || !input_str || !*input_str)
		return (1);
	if (init_tokens)
		return (parse_error("Failed: tokenize_init()", 1)); //check for actual  bash error code

}
