#include "minishell.h"

void	ft_unset(t_env **env, char *key)
{
	t_env	*variable;
	// int		size;
	int		i;
	int j = 0;
	// printf("%s\n", key);

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


// 	if (variable)
// 	{
// 		free()
// 	}
// }