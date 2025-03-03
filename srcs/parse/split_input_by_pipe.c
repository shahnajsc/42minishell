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

	part_cmd = (char *)malloc(sizeof(char) * (len + 1));
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

static char *get_end_point(char *input_str)
{
	while (*input_str)
	{
		if (check_char_is_quote(*input_str))
			input_str = skip_quoted_part(input_str);
		else if (*input_str == '|')
			break;
		else
			input_str++;
	}
	return (input_str);
}

static char	**splitted_by_pipe(char *input_str, char **cmds_temp, int cmd_count, int i)
{
	char	*start;
	char	*end;
	int		len;

	while (++i < cmd_count)
	{
		if (*input_str && *input_str == '|')
			input_str++;
		start = input_str;
		end = get_end_point(input_str);
		input_str = end;
		len = get_cmd_len(start, end);
		cmds_temp[i] = get_part_cmd(start, end, len);
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
	if (!input_str || input_str[0] == '\0' || check_str_whitespaces(input_str))
		return (NULL);
	cmds_temp = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmds_temp)
		return (NULL);
	cmds_temp = splitted_by_pipe(input_str, cmds_temp, cmd_count, -1);
	if (!cmds_temp)
	{
		printf("no splitted cmds sp function\n");
		return (NULL);
	}
	return (cmds_temp);
}
