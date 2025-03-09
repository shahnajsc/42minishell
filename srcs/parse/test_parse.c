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
void print_token_list(t_token *token_list)
{
	int i;
	t_token *temp;

	i = 0;
	temp = token_list;
	while (temp)
	{
		printf("::token[%d] type:[%u][%s]\n", i, temp->tok_type,  temp->tok_value);
		temp = temp->next;
		i++;
	}
	printf("\n");
}

void print_splitted_cmd_list(char **cmds, char *name)
{
	int i;

	i = 0;
	printf("::cmd_name:[%s]  cmds", name);
	while (cmds[i])
	{
		printf("[%s] ", cmds[i]);
		i++;
	}
	printf("\n");
}

void print_command_list(t_mshell *mshell)
{
	int i;

	i = 0;
	// printf("....COMMANDS SPLITTED BY PIPE....\n");
	while (i < mshell->count_cmds)
	{
		printf("____________________________\n");
		printf("COMMAND[%d][%s]\n", i, mshell->cmds[i].cmd_str);
		printf("TOKENS\n");
		print_token_list(mshell->cmds[i].token);
		printf("CMDS\n");
		print_splitted_cmd_list(mshell->cmds[i].splitted_cmd, mshell->cmds[i].cmd_name);
		printf("____________________________\n");
		i++;
	}
	printf("\n");
}


