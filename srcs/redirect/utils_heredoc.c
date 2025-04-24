/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:06:37 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 19:16:46 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mem_alloc_failed(char **joined_lines, char *line)
{
	if (joined_lines && *joined_lines)
	{
		free(*joined_lines);
		*joined_lines = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	ft_putstr_fd("minishell: malloc failed for heredoc!\n", STDERR_FILENO);
	return (1);
}

int	heredoc_join(char **joined_lines, char *line)
{
	char	*ptr;
	char	*ptrcat;
	int		i;
	int		len;

	len = ft_strlen(*joined_lines) + ft_strlen(line);
	ptr = (char *)malloc(sizeof(char) * (len + 2));
	if (!ptr)
		return (mem_alloc_failed(joined_lines, line));
	ptrcat = ptr;
	i = 0;
	while (*joined_lines && (*joined_lines)[i])
		*ptr++ = (*joined_lines)[i++];
	i = 0;
	while (line && line[i])
		*ptr++ = line[i++];
	*ptr++ = '\n';
	*ptr = '\0';
	if (*joined_lines)
		free(*joined_lines);
	if (line)
		free(line);
	*joined_lines = ptrcat;
	return (0);
}
