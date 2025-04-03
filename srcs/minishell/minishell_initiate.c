/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initiate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:52:21 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 23:16:28 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_execute(t_mshell *mshell)
{
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
		else
		{
			if (*input_str)
				add_history(input_str);
			if (parse_input(mshell, input_str))
			{
				free(input_str);
				continue ;
			}
			free(input_str);
			start_execute(mshell);
		}
	}
	rl_clear_history();
	return (mshell->exit_code);
}
