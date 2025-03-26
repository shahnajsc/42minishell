/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:53:13 by shachowd          #+#    #+#             */
/*   Updated: 2025/03/26 09:14:45 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_buffer(int fd, char *read_buf, char *left_buf)
{
	ssize_t	read_bytes;
	char	*tmp_left_buffer;

	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(left_buf, '\n'))
	{
		read_bytes = read(fd, read_buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			return (NULL);
		}
		if (read_bytes == 0)
		{
			break ;
		}
		read_buf[read_bytes] = '\0';
		tmp_left_buffer = left_buf;
		left_buf = ft_strjoin(left_buf, read_buf);
		free(tmp_left_buffer);
	}
	free(read_buf);
	return (left_buf);
}

static char	*get_line(char *left_buf)
{
	size_t	len;
	size_t	count;
	char	*line;

	if (!left_buf)
		return (NULL);
	len = ft_len_line(left_buf);
	count = 0;
	line = malloc((len + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	while (left_buf[count] != '\0' && left_buf[count] != '\n')
	{
		line[count] = left_buf[count];
		count++;
	}
	if (left_buf[count] == '\n')
	{
		line[count] = left_buf[count];
		count++;
	}
	line[count] = '\0';
	return (line);
}

static char	*get_left(char *string)
{
	char	*left_buf;
	size_t	count;

	count = 0;
	while (string[count] != '\n' && string[count] != '\0')
		count++;
	if (string[count] == '\0')
	{
		free(string);
		return (NULL);
	}
	left_buf = ft_substr(string, count + 1, ft_strlen(string) - count);
	if (!left_buf || ft_strlen(left_buf) == 0)
	{
		free(string);
		free(left_buf);
		return (NULL);
	}
	free(string);
	return (left_buf);
}

static void	free_null(char **string)
{
	free(*string);
	*string = NULL;
}

char	*get_next_line(int fd)
{
	char		*read_buf;
	static char	*left_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free_null(&left_buf);
		return (NULL);
	}
	read_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buf)
	{
		free_null(&left_buf);
		return (NULL);
	}
	left_buf = get_buffer(fd, read_buf, left_buf);
	line = get_line(left_buf);
	if (!line)
	{
		free_null(&left_buf);
		return (NULL);
	}
	left_buf = get_left(left_buf);
	return (line);
}
