#include "minishell.h"

void		echo_pwd_oldpwd(t_mshell *mshell, char *key)
{
	t_env	*variable;
	char	*env_value;

	variable = find_env_var(mshell->env, key);
	env_value = variable ? variable->value : NULL;
	if (env_value)
		ft_putstr_fd(env_value, STDOUT_FILENO);
	if (mshell->b_state->oldpwd_exec && ft_strcmp(key, "OLDPWD") == 0 && mshell->b_state->old_pwd)
			ft_putstr_fd(mshell->b_state->old_pwd, STDOUT_FILENO);
	if (mshell->b_state->pwd_exec && ft_strcmp(key, "PWD") == 0 && mshell->b_state->pwd)
			ft_putstr_fd(mshell->b_state->pwd, STDOUT_FILENO);
}
int	is_newline(char *c, int *nl)
{
	if (ft_strcmp(c, "-n") == 0)
	{
		*nl= 0;  
		return (1);  
	}
	*nl = 1;  
	return (0);
}
void	ft_echo(t_mshell *mshell, char **args)
{
	int 		i;
	int 		new_line;
	t_env 		*variable;

	i = 1;
	new_line = 1;
	if (args[i] && is_newline(args[i], &new_line))
		i++;
	while (args[i] != NULL)
	{
		variable = find_env_var(mshell->env, args[i]);
		if (variable && variable->value)
			ft_putstr_fd(variable->value, STDOUT_FILENO);
		else
			ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);	
}
