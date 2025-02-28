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

static int shell_state(t_mshell *mshell, char *oldpwd, char *pwd)
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
			return(builtins_error(NULL, CMN_ERR, "minishell: getcwd failed for state->pwd", NULL));
	}
	free(mshell->b_state->old_pwd);
	free(mshell->b_state->pwd);
	mshell->b_state->old_pwd = new_oldpwd;
	mshell->b_state->pwd = new_pwd;
	mshell->b_state->pwd_exec = (find_env_var(mshell->env, "PWD") == NULL);
	mshell->b_state->oldpwd_exec = (find_env_var(mshell->env, "OLDPWD") == NULL);
	return (SUCSSES);
}

static void	update_cd_env(t_env **env, const char *key, const char *set_path)
{
	t_env	*variable;
	char	*temp;

	variable = find_env_var(*env, (char *)key);
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
void	update_built_state(t_mshell *mshell, char *oldpwd, char *pwd)
{
	shell_state(mshell, oldpwd, pwd);
	if (find_env_var(mshell->env, "OLDPWD"))
		update_cd_env(&mshell->env, "OLDPWD", oldpwd);
	if (find_env_var(mshell->env, "PWD"))
		update_cd_env(&mshell->env, "PWD", pwd);
}
