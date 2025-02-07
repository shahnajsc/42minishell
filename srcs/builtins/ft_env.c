#include "minishell.h"


///"srcs/includes/minishell.h"



int get_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}


t_env	*init_env(char **env)
{
	int size;
	char *env_var;
	int i;
	char *sign;
	int key_len;

	size = get_env(env);
	env_var = (t_env *)malloc(sizeof(t_env) * (size + 1));
	i = 0;
	while (i <  size)
	{
		sign = ft_strchr(env[i], '=');
		if (sign)
		{
			
		}
	}

}

