/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initiate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:52:21 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 16:41:46 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interrupt_input(t_mshell *mshell)
{
	if (g_store_sigint == SIGINT)
	{
		g_store_sigint = 0;
		mshell->exit_code = 130;
		return (1);
	}
	return (0);
}

void	initiate_minishell(t_mshell *mshell, char *input_str)
{
	add_history(input_str);
	if (parse_input(mshell, input_str))
	{
		free(input_str);
		return ;
	}
	free(input_str);
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
		g_store_sigint = 0;
		input_str = readline(PROMPT);
		if (!input_str)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		interrupt_input(mshell);
		if (input_str && *input_str)
			initiate_minishell(mshell, input_str);
	}
	rl_clear_history();
	return (mshell->exit_code);
}
