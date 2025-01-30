/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:49:42 by shachowd          #+#    #+#             */
/*   Updated: 2024/12/20 13:42:01 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*line_mem_realloc(char *line, int new_buf_size)
{
	char	*new_line;

	new_line = (char *)malloc(new_buf_size * sizeof(char));
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	ft_memcpy((char *)new_line, line, new_buf_size / 2);
	free(line);
	return (new_line);
}

static void	read_check(int read_byte, char **line, int i)
{
	if (read_byte == -1)
	{
		free(*line);
		*line = NULL;
	}
	if (read_byte == 0 && i == 0)
	{
		free(*line);
		*line = NULL;
	}
}

char	*ft_line_reader(int fd, char *line, int buffer, int index)
{
	int		read_byte;
	char	read_char;

	line = (char *)malloc(sizeof(char) * buffer);
	if (!line)
		return (NULL);
	while (1)
	{
		read_byte = read(fd, &read_char, 1);
		read_check(read_byte, &line, index);
		if (!line || read_byte == 0)
			break ;
		line[index++] = read_char;
		if (read_char == '\n')
			break ;
		if (index >= buffer)
		{
			buffer += buffer;
			line = line_mem_realloc(line, buffer);
		}
	}
	if (line)
		line[index] = '\0';
	return (line);
}
