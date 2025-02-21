#include "minishell.h"

static int	get_cmd_len(char *start, char *end)
{
	int		len;

	len = 0;
	while (start < end)
	{
		len++;
		start++;
	}
	return (len);
}

static char	*get_part_cmd(char *start, char *end, int len)
{
	char	*part_cmd;
	int		index;

	part_cmd = (char *)malloc(sizeof(char) * len + 1);
	if (!part_cmd)
		return (NULL);
	index = 0;
	while (start < end)
	{	part_cmd[index++] = *start;
		start++;
	}
	part_cmd[index] = '\0';
	return (part_cmd);
}

static char	**splitted_cmd(char *input_str, char **cmds_temp, int cmd_count, int i)
{
	char	*start;
	char	*end;
	int		len;

	while (++i < cmd_count + 1)
	{
		printf("i: %d\n", i);
		while (*input_str && check_char_whitespaces(*input_str))
			input_str++;
		if (*input_str && *input_str == '|')
			input_str++;
		start = input_str;
		if (*input_str && check_char_is_quote(*input_str))
			input_str = skip_quoted_part(input_str);
		while (*input_str && *input_str != '|')
			input_str++;
		end = input_str;
		len = get_cmd_len(start, end);
		cmds_temp[i] = get_part_cmd(start, end, len);
		printf("c[%d] : value[%s]\n", i, cmds_temp[i]);
		if (!cmds_temp[i])
		{
			ft_free_grid((void *)cmds_temp);
			return (NULL);
		}
	}
	cmds_temp[i] = NULL;
	return (cmds_temp);
}

char	**split_input_by_pipes(int cmd_count, char *input_str)
{
	char	**cmds_temp;
	//printf("split function begin \n");
	if (!input_str || input_str[0] == '\0' || check_str_whitespaces(input_str))
		return (NULL);
	//printf("split function not null \n");
	cmds_temp = (char **)malloc(sizeof(char) * cmd_count + 1);
	if (!cmds_temp)
		return (NULL);
	//printf("split function mem allocated \n");
	cmds_temp = splitted_cmd(input_str, cmds_temp, cmd_count, -1);
	printf("\n");
	if (!cmds_temp)
	{
		printf("no splitted cmds sp function\n");
		return (NULL);
	}
	//printf("split function splitted\n");
	// int i = 0;
	// while (cmds_temp[i] != NULL)
	// {
	// 	printf("b[%d] : value[%s]\n", i, cmds_temp[i]);
	// 	i++;
	// }
	// printf("\n");
	return (cmds_temp);
}
