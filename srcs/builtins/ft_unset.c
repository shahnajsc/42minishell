// #include "minishell.h"

// void	ft_unset(t_env **env, char *key)
// {
// 	t_env 	*variable;
// 	int 	size;
// 	int 	i;

// 	variable = find_env_var(*env, key);
// 	if (!variable)
// 		return ;
// 	size = env_size(env);
// 	while (i < size)
// 	{
// 		if (&(*env)[i] == variable)
// 		{
// 			free((*env)[i].key);
// 			free((*env)[i].value);
// 			break ;
// 		}
// 	}
// }
// // 	if (variable)
// // 	{
// // 		free()
// // 	}
// // }
