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

	ft_putstr_fd("minishell: memory allocation failed for heredoc!\n", STDERR_FILENO);
	return (1);
}

int	heredoc_join(char **joined_lines, char *line)
{
	char			*ptr;
	char			*ptrcat;
	int				i;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(*joined_lines) + ft_strlen(line) + 2));
	if (!ptr)
		return(mem_alloc_failed(joined_lines, line));
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

void	get_hd_lines(t_mshell *mshell, t_redirect *rd_list, int i, int is_quote)
{
	char *line;
	char *joined_lines;

	if (!mshell || !rd_list)
		return ;
	joined_lines = ft_strdup("");
	if (!joined_lines)
		return ;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, rd_list[i].file_deli) == 0)
		{
			free(line);
			break ;
		}
		if (heredoc_join(&joined_lines, line))
		{
			free(joined_lines);
			return ;
		}
	}
	rd_list[i].hd_lines = expand_heredoc(mshell, joined_lines, is_quote);
	//printf("hd: %s", rd_list[i].hd_lines);
	//mshell->exit_code = 112;
}

int	heredoc_handle(t_mshell *mshell)
{
	int	i;
	int	j;
	int	rd_len;

	i = 0;
	while (mshell->cmds && i < mshell->count_cmds)
	{
		j = 0;
		rd_len = get_rd_list_len(mshell->cmds[i].token);
		while (j < rd_len)
		{
			if (mshell->cmds[i].redirects[j].rd_type == RD_HEREDOC)
			{
				get_hd_lines(mshell, mshell->cmds[i].redirects, j, \
				mshell->cmds[i].is_hd_quote);
				if (!mshell->cmds[i].redirects[j].hd_lines)
					return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
