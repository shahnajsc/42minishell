#include "minishell.h"

// void 	ft_unset(t_env **env, char *key)
// {
// 	t_env  		*variable;
// 	t_env 		*new_env;
// 	int 		i;
// 	int 		index;

// 	if (!env || !*env || !key)
// 		return ;
// 	i = 0;
// 	index = 0;
// 	variable = get_env_var(*env, key);
// 	if (!variable)
// 		return ;
// 	i = env_size(*env);
// 	new_env = allocate_new_env(env);
// 	if (!new_env)
// 		return ;
// 	while ((*env)[i].key != NULL)
// 	{
// 		if (&(*env)[i] != variable)
// 		{
// 			new_env[index].key = ft_strdup((*env)[i].key);
// 			if ((*env)[i].value)
// 				new_env[index].value = ft_strdup((*env)[i].value);
// 			else
// 				new_env[index].value = NULL;
// 			if (!new_env[index].key || (!new_env[index].value && (*env)[i].value))
//             {
//                 free_env(new_env);
//                 return;
//             }
// 			index++;
// 		}
// 		i++;
// 	}
// 	new_env[index].key = NULL;
//     new_env[index].value = NULL;
//     free_env(*env);
//     *env = new_env;
// }


void	ft_unset(t_env **env, char *key)
{
	t_env	*variable;
	int		i;
	int j = 0;

	if (!env || !*env || !key)
		return;

	variable = get_env_var(*env, key);
	if (!variable)
		return;

	while ((*env)[j].key != NULL)
		j++;
	i = 0;
	while (i < j)
	{
		if (&(*env)[i] == variable)
		{
			free((*env)[i].key);
			free((*env)[i].value);
			
			// Shift remaining elements left
			while (i < j - 1)
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}

			// Nullify the last element
			(*env)[j - 1].key = NULL;
			(*env)[j - 1].value = NULL;

			return;
		}
		i++;
	}
}

