/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:49:04 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/01 20:59:02 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_env *env)
{
	int	i;

	i = -1;
	while (env[++i].key != NULL)
	{
		if (env[i].value != NULL)
		{
			if (env[i].key && (env)[i].key[0] != '\0')
			{
				ft_putstr_fd(env[i].key, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
			}
			ft_putendl_fd(env[i].value, STDOUT_FILENO);
		}
	}
}

int	ft_env(t_mshell *mshell, char **args)
{
	int	status;

	status = 0;
	if (!mshell || !mshell->env || !args)
		return (0);
	if (!args[1])
		print_env(mshell->env);
	else if (!*args[1] || args[1])
	{
		ft_putstr_fd("env: ‘", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd("’: No such file or directory", STDERR_FILENO);
		status = 127;
	}
	return (status);
}
