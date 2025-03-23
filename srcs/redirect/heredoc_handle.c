#include "minishell.h"

static int	mem_alloc_failed(char **hd, char *line)
{
	if (hd && *hd)
	{
		free(*hd);
		*hd = NULL;
	}
	if (line)
		free(line);
	ft_putstr_fd("minishell: memory allocation failed for heredoc!\n", STDERR_FILENO);
	return (1);
}

int	heredoc_join(char **hd, char *line)
{
	char			*ptr;
	char			*ptrcat;
	int				i;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(*hd) + ft_strlen(line) + 2));
	if (!ptr)
		return(mem_alloc_failed(hd, line));
	ptrcat = ptr;
	i = 0;
	while (*hd && (*hd)[i])
		*ptr++ = (*hd)[i++];
	i = 0;
	while (line && line[i])
		*ptr++ = line[i++];
	*ptr++ = '\n';
	*ptr = '\0';
	if (*hd)
		free(*hd);
	if (line)
		free(line);
	*hd = ptrcat;
	return (0);
}

void	heredoc_handle(t_mshell *mshell, t_redirect *rd_list, int i)
{
	char *line;
	char *hd_lines;

	// if (!hd_lines || rd_list)
	// 	return ;
	if (!rd_list)
		printf("no rd list\n");
	hd_lines = ft_strdup("");
	if (!hd_lines)
	{
		printf("error hd\n");
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			//print error and check if it is interupted by SIG
			break ; // or exit??
		}
		if (ft_strncmp(line, rd_list[i].file_deli, ft_strlen(rd_list[i].file_deli)) == 0) // && line[ft_strlen(deli) + 1] == '\n'
		{
			free(line);
			break ;
		}
		if (heredoc_join(&hd_lines, line))
			return ;
	}
	free(rd_list[i].file_deli);
	rd_list[i].file_deli = hd_lines;
	mshell->exit_code = 112;
}
