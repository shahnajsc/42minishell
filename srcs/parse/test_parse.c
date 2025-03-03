#include "minishell.h"

void	tokens_print(t_token *token)
{
	t_token *current = token;

	while (current)
	{
		printf("type[%u], value[%s]\n", current->tok_type, current->tok_value );
		current = current->next;
	}
	printf("\n");
}

void	print_splitted_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		printf("id[%d][%s]\n", i, cmds[i]);
		i++;
	}
	printf("\n");
}
