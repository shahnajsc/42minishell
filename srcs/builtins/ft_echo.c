#include "minishell.h"

void		echo_pwd_oldpwd(t_env **env, t_shell_state *state, char *key)
{
	t_env	*variable;
	char	*env_value;

	variable = find_env_var(*env, key);
	env_value = variable ? variable->value : NULL;
	if (env_value)
		ft_putstr_fd(env_value, STDOUT_FILENO);
	else if (state->cd_executed)
	{
		if (ft_strcmp(key, "OLDPWD") == 0 && state->old_pwd)
			ft_putstr_fd(state->old_pwd, STDOUT_FILENO);
		else if (ft_strcmp(key, "PWD") == 0 && state->pwd)
			ft_putstr_fd(state->pwd, STDOUT_FILENO);
	}
	// ft_putstr_fd("\n", STDOUT_FILENO);
}


void	ft_echo(t_env **env, t_shell_state *state, char *str)
{
	char 	*key;
	t_env 	*env_var;

	if (!str)
		return ;
	if (ft_strchr("$", *str))
	{
		key = str + 1;
		if (ft_strcmp(key, "PWD") == 0 || ft_strcmp(key, "OLDPWD") == 0 )
			echo_pwd_oldpwd(env, state, key);
		else
		{
			env_var = find_env_var(*env, key);
			if (env_var->value)
				ft_putstr_fd(env_var->value, STDOUT_FILENO);
		}
		ft_putchar_fd('\n', 1);
		return ;
	}
	if (str != NULL)
		ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}


// void 	ft_nl(char *str)
// {
// 	if (!str)
// 		return ;
// 	if (ft_strchr(*str, 'n'))
// 		ft_putstr_fd(str, 1);
// }
//echo $home
//echo /haamda/abc/

//echo -n $abc
//echo -n 