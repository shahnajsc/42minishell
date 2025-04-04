/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initiate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:52:21 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/04 13:51:11 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void interrupt_input(t_mshell *mshell)
{
	if (g_heredoc == SIGINT)
	{
		g_heredoc = 0;
		mshell->exit_code = 130;
	}
}
void handle_all(t_mshell *mshell, char *line)
{
	if (*line)
		add_history(line);
	if (mshell->cmds)
		execute_cmds(mshell);
	cleanup_on_loop(mshell);
}

int	minishell(t_mshell *mshell)
{
	char	*input_str;

	setup_signal_handlers();
	while (1)
	{
		g_heredoc = 0;
		input_str = readline(PROMPT);
		if (!input_str)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		interrupt_input(mshell);
		if (parse_input(mshell, input_str))
		{
			free(input_str);
			continue ;
		}
		handle_all(mshell, input_str);
	}
	rl_clear_history();
	return (mshell->exit_code);
}
