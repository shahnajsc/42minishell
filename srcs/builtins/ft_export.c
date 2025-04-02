/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:49:38 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/01 20:49:39 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env(t_env *a, t_env *b)
{
	t_env	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env(t_env *env)
{
	int	swapped;
	int	i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (env[i].key != NULL && env[i + 1].key != NULL)
		{
			if (compare_keys(env[i].key, env[i + 1].key) > 0)
			{
				swap_env(&env[i], &env[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}

static void	set_env_var(t_mshell *mshell, char **args, int *status_code)
{
	char	*sign;
	int		i;

	i = 1;
	while (args[i] != NULL)
	{
		if (is_invalid_identifier(args[i]))
			*status_code = 1;
		else
		{
			sign = ft_strchr(args[i], '=');
			if (!sign)
				process_without_sign(&mshell->env, args[i]);
			else
				process_with_sign(&mshell->env, args[i], sign);
		}
		i++;
	}
}

static void	print_export(t_env *env)
{
	int	i;

	sort_env(env);
	i = 0;
	while (env[i].key != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i].key, 1);
		if (env[i].value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env[i].value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	ft_export(t_mshell *mshell, char **args)
{
	int	status;

	if (!mshell || !mshell->env || !args)
		return (0);
	status = 0;
	if (!args[1])
		print_export(mshell->env);
	else
		set_env_var(mshell, args, &status);
	return (status);
}
