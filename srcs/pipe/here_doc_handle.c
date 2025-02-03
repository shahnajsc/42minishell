/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:03:44 by shachowd          #+#    #+#             */
/*   Updated: 2025/01/31 17:39:31 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*line_mem_realloc(char *line, int new_buf_size, int hd_fd)
{
	char	*new_line;

	new_line = (char *)malloc(new_buf_size * sizeof(char));
	if (!new_line)
	{
		free(line);
		read_err_return("malloc()", "", hd_fd);
	}
	ft_memcpy((char *)new_line, line, new_buf_size / 2);
	free(line);
	return (new_line);
}

static void	read_check(int read_byte, char **line, int hd_fd, int i)
{
	if (read_byte == -1)
		read_err_return("read()", *line, hd_fd);
	if (read_byte == 0 && i == 0)
	{
		free(*line);
		*line = NULL;
	}
}

static char	*read_line(int fd, int hd_fd, int i, int buffer_size)
{
	char	*line;
	int		read_byte;
	char	read_char;

	line = (char *)malloc(sizeof(char) * buffer_size);
	if (!line)
		read_err_return("malloc()", "", hd_fd);
	while (1)
	{
		read_byte = read(fd, &read_char, 1);
		read_check(read_byte, &line, hd_fd, i);
		if (!line || read_byte == 0)
			break ;
		line[i++] = read_char;
		if (read_char == '\n')
			break ;
		if (i >= buffer_size)
		{
			buffer_size += buffer_size;
			line = line_mem_realloc(line, buffer_size, hd_fd);
		}
	}
	if (line)
		line[i] = '\0';
	return (line);
}

void	read_here_doc(t_pipex *data)
{
	char	*line_text;
	int		hd_fd;

	hd_fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (hd_fd == 1)
		error_return(data, "open()", "", 0);
	while (1)
	{
		line_text = read_line(0, hd_fd, 0, BUFFER_SIZE);
		if (!line_text)
			break ;
		if (ft_strncmp(line_text, data->argv[2], ft_strlen(line_text) - 1) == 0)
		{
			free(line_text);
			break ;
		}
		ft_putstr_fd(line_text, hd_fd);
		free(line_text);
	}
	close(hd_fd);
}
