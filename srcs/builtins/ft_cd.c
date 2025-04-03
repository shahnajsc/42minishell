/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:48:49 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 13:15:07 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*home_directory(t_env **env, char **dir, int *status, int i)
{
	t_env	*variable;

	variable = get_env_var(*env, "HOME");
	if (!variable || !variable->value)
	{
		if (i == 0)
			*status = 1;
		else
			*status = 0;
		return  (NULL);
	}
	*dir = ft_strdup(variable->value);
	if (!*dir)
		return (NULL);
	return (*dir);
}

static char	*get_target_directory(t_env **env, char **args, int *status)
{
	char	*target;

	if (!args[1])
	{
		target = home_directory(env, &target, status, 0);
		if (!target)
			return (cd_error(args, HOME_UNSET), NULL);
	}
	else if (ft_strcmp(args[1], "~") == 0)
	{
		target = home_directory(env, &target, status, 1);
		if (!target)
			return (NULL);
	}
	else
	{
		target =  ft_strdup(args[1]);
		if (!target)
		{
			*status = 1;
			return (NULL);
		}
	}
	return (target);
}


static int	is_invalid_directory(char **args, char *file)
{
	struct stat	sb;

	if (args[1] && args[2])
		return (MANY_ARGS);
	if (!*file)
		return (EXIT_SUCCESS);
	if (stat(file, &sb) == -1)
		return (NO_FILE);
	if (!S_ISDIR(sb.st_mode))
		return (NOT_DIR);
	if ((sb.st_mode & (S_IRUSR | S_IRGRP)) == 0
		|| (sb.st_mode & (S_IWUSR | S_IWGRP)) == 0
		|| (sb.st_mode & (S_IXUSR | S_IXGRP)) == 0)
		return (NO_PERM);
	return (EXIT_SUCCESS);
}

static int	handle_cd(t_mshell *mshell, char **args, int *status)
{
	t_cd_error	error_code;
	char		*new_pwd;
	char		*target;

	target = get_target_directory(&mshell->env, args, status);
	if (!target)
		return (*status);
	error_code = is_invalid_directory(args, target);
	if (error_code != EXIT_SUCCESS)
		return (free(target), cd_error(args, error_code));
	if (chdir(target) == -1)
		return (free(target), 0);
	free(target);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (cd_error(args, GETCWD));
	if (update_env_state(mshell, new_pwd) != EXIT_SUCCESS)
		return (free(new_pwd), 0);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_mshell *mshell, char **args)
{
	int	status;

	if (!mshell || !mshell->env || !args)
		return (0);
	status = handle_cd(mshell, args, &status);
	return (status);
}
