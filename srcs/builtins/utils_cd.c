#include "minishell.h"

t_built_state 	*init_built_state()
{
	t_built_state *state;

	state = (t_built_state *)malloc(sizeof(t_built_state));
	if (!state)
	{
		ft_putendl_fd("minishell: shell state", STDERR_FILENO);
		return (NULL);
	}
	state->pwd = getcwd(NULL, 0);
	if (!state->pwd)
	{
		free(state->pwd);
		ft_putendl_fd("minishell: getcwd failed", STDERR_FILENO);
		return (NULL);
	}
	state->old_pwd = NULL;
	state->pwd_exec = 0;
	state->oldpwd_exec = 0;
	return (state);
}

 int shell_state(t_mshell *mshell, char *oldpwd, char *pwd)
{
	char *new_oldpwd;
	char *new_pwd;

	new_oldpwd = ft_strdup(oldpwd);
	new_pwd = ft_strdup(pwd);
	if (!new_oldpwd || !new_pwd)
	{
		free(new_oldpwd);
		free(new_pwd);
		mshell->b_state->pwd = getcwd(NULL, 0);
		mshell->b_state->old_pwd = NULL;
		if (!mshell->b_state->pwd)
			return(builtins_error(NULL, "getcwd failed for state->pwd", NULL));
	}
	free(mshell->b_state->old_pwd);
	free(mshell->b_state->pwd);
	mshell->b_state->old_pwd = new_oldpwd;
	mshell->b_state->pwd = new_pwd;
	mshell->b_state->pwd_exec = (get_env_var(mshell->env, "PWD") == NULL);
	mshell->b_state->oldpwd_exec = (get_env_var(mshell->env, "OLDPWD") == NULL);
	return (SUCSSES);
}

void	update_cd_env(t_env **env, const char *key, const char *set_path)
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
	t_env 	*current_env_pwd;
	t_env 	*prev_pwd;

	prev_pwd = get_env_var(mshell->env, "OLDPWD");
	if (!prev_pwd || !prev_pwd->value)
		return (1);
	current_env_pwd = get_env_var(mshell->env, "PWD");
	if (!current_env_pwd || !current_env_pwd->value)
		return (1);
	update_cd_env(&mshell->env, "OLDPWD", current_env_pwd->value);
	update_cd_env(&mshell->env, "PWD", current_pwd);
	// if (shell_state(mshell, prev_pwd->value, current_pwd))
	// 	return (1);
	free(current_pwd);
	return (0);
}

