#include  "minishell.h"

// int	read_check(int read_byte, char *line)
// {
// 	if (read_byte == -1)
// 	{
// 		if (line)
// 			free(line);
// 		ft_putstr_fd("readline: heredoc read failed\n", 2);
// 		return (-1);
// 	}
// 	return (read_byte);
// }

static int	get_rl_str_len(char *read_text)
{
	int	i;

	i = 0;
	while (read_text[i])
	{
		if (read_text[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

static char	*readline_str_join(char *line, char *read_text)
{
	char	*joined_str;
	size_t	len_line;
	int	len_read;

	if (!line)
		len_line = 0;
	else
		len_line = ft_strlen(line);
	len_read = get_rl_str_len(read_text);
	joined_str = (char *)malloc(len_line + len_read + 1);
	if (!joined_str)
		return (NULL);
	if (line)
		ft_strlcpy(joined_str, line, len_line + 1);
	ft_strlcpy(joined_str + len_line, read_text, len_read + 1);
	free(line);
	return (joined_str);
}

char	*read_line(int fd)
{
	char	*line;
	int		read_byte;
	char	read_text[BUFFER_SIZE + 1]; // +1 ????

	line = NULL;
	while (1)
	{
		ft_memset(read_text, 0, BUFFER_SIZE + 1); // +1 ????
		read_byte = read(fd, read_text, BUFFER_SIZE);
		if (read_byte == -1)
		{
			if (line)
				free(line);
			ft_putstr_fd("readline: heredoc read failed\n", 2);
			return (NULL);
		}
		else if (read_byte == 0)
			break ;
		line = readline_str_join(line, read_text);
		if (!line)
			return (NULL);
		if (ft_strchr(read_text, '\n'))
			break ;
	}
	return (line);
}
