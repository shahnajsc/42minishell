/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:54:54 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 18:14:35 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_error(t_mshell *mshell, char *err_value, char *err_msg, int err_code)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	if (err_value)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err_value, STDERR_FILENO);
	}
	if (err_msg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(err_msg, STDERR_FILENO);
	}
	mshell->exit_code = err_code;
	return (-1);
}
