/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:52:44 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 10:58:39 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_mshell *mshell, char *input_str)
{
	if (!input_str)
		return (EXIT_FAILURE);
	if (input_str && !*input_str)
		return (EXIT_SUCCESS);
	if (pre_validation_input(mshell, input_str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (tokenize_input(mshell, input_str))
	{
		//mshell->exit_code = 0; // check other exit failure
		cleanup_on_loop(mshell);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
