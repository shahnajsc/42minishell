/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:49:38 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 16:43:48 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	export_duplicate(t_env **copy_env, t_env *env)
{
	int	count;
	int	i;

	count = 0;
	while (env[count].key != NULL)
		count++;
	*copy_env = malloc(sizeof(t_env) * (count + 1));
	if (!*copy_env)
		return (EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		if (export_copy(&(*copy_env)[i], &env[i]))
		{
			free_env(*copy_env);
			return (EXIT_FAILURE);
		}
		i++;
	}
	(*copy_env)[count].key = NULL;
	(*copy_env)[count].value = NULL;
	return (EXIT_SUCCESS);
}

static void	print_export(t_env *env)
{
	t_env	*copy_env;
	int		i;

	if (export_duplicate(&copy_env, env) != EXIT_SUCCESS)
		return ;
	sort_env(copy_env);
	i = 0;
	while (copy_env[i].key != NULL)
	{
		if (ft_strcmp(copy_env[i].key, "_") != 0)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(copy_env[i].key, STDOUT_FILENO);
			if (copy_env[i].value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(copy_env[i].value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	free_env(copy_env);
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
