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

void restore_signals(struct sigaction *old_sa)
{
    if (old_sa) 
        sigaction(SIGINT, old_sa, NULL);
    rl_catch_signals = 1;  // Restore readline's default signal handling
	rl_event_hook = NULL;
}

void get_hd_lines(t_mshell *mshell, t_redirect *rd_list, int i, int is_quote)
{
	struct sigaction sa_old;
	char 			*joined_lines;
    char 			*line;
	
	if (!mshell || !rd_list)
		return ;
	setup_heredoc_signals(&sa_old);
    /* Configure readline for immediate response */
    rl_event_hook = heredoc_event_hook;
    rl_catch_signals = 0;  // Let our handler manage signals
    g_heredoc = 0;


    if (!(joined_lines = ft_strdup("")))
        return;
    while (!g_heredoc)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, rd_list[i].file_deli) == 0)
        {
            free(line);
            break;
        }
        if (heredoc_join(&joined_lines, line))
            break;
    }
    restore_signals(&sa_old);
    if (!g_heredoc)
        rd_list[i].hd_lines = expand_heredoc(mshell, joined_lines, is_quote);
	else
		free(joined_lines);
    g_heredoc = 0;
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
