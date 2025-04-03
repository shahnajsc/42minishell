/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:50:15 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 13:39:42 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	update_cd(t_env **env, const char *key, const char *set_path)
{
	t_env	*variable;
	char	*temp;

	variable = get_env_var(*env, (char *)key);
	if (!variable)
		return ;
	temp = ft_strdup(set_path);
	if (!temp)
	{
		ft_putendl_fd("Error: allocation failed", STDERR_FILENO);
		return ;
	}
	free(variable->value);
	variable->value = temp;
}

int	update_env_state(t_mshell *mshell, char *current_pwd)
{
	t_env	*current_env_pwd;
	t_env	*prev_pwd;

	prev_pwd = get_env_var(mshell->env, "OLDPWD");
	if (!prev_pwd || !prev_pwd->value)
		return (EXIT_FAILURE);
	current_env_pwd = get_env_var(mshell->env, "PWD");
	if (!current_env_pwd || !current_env_pwd->value)
		return (EXIT_FAILURE);
	update_cd(&mshell->env, "OLDPWD", current_env_pwd->value);
	update_cd(&mshell->env, "PWD", current_pwd);
	free(current_pwd);
	return (EXIT_SUCCESS);
}
