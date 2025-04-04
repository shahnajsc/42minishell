/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:55:10 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/04 13:46:24 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_signals(struct sigaction *old_sa)
{
	if (old_sa)
		sigaction(SIGINT, old_sa, NULL);
	rl_catch_signals = 1;
	rl_event_hook = NULL;
}

static void	heredoc_warning(char *delimeter)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimeter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

static int	heredoc_input(char **joined_lines, char *delimeter)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		heredoc_warning(delimeter);
		return (1);
	}
	if (ft_strcmp(line, delimeter) == 0)
	{
		free(line);
		return (1);
	}
	if (heredoc_join(joined_lines, line))
		return (1);
	return (0);
}

static int	get_hd_lines(t_mshell *mshell, t_redirect *rd_list,
	int i, int is_quote)
{
	struct sigaction	sa_old;
	char				*joined_lines;

	if (!mshell || !rd_list)
		return (1);
	setup_heredoc_signals(&sa_old);
	rl_event_hook = heredoc_event_hook;
	rl_catch_signals = 0;
	joined_lines = NULL; //ft_strdup("");
	if (!joined_lines)
		return (1);
	while (!g_heredoc)
	{
		if (heredoc_input(&joined_lines, rd_list[i].file_deli))
			break ;
	}
	restore_signals(&sa_old);
	if (!g_heredoc)
		rd_list[i].hd_lines = expand_heredoc(mshell, joined_lines, is_quote);
	else
		free(joined_lines);
	return (0);
}

int	heredoc_handle(t_mshell *mshell, int *status)
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
				*status = get_hd_lines(mshell, mshell->cmds[i].redirects, j,
					mshell->cmds[i].is_hd_quote);
			}
			j++;
		}
		i++;
	}
	return (EXIT_FAILURE);
}
