/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_mshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:52:15 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/01 20:52:16 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_mshell(t_mshell *mshell)
{
	if (!mshell)
		return ;
	if (mshell->env)
		free_env(mshell->env);
	if (mshell->cmds)
		cleanup_on_loop(mshell);
}
