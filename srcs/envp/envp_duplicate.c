#include "./minishell.h"

char	**envp_duplicate(char **envp)
{
	char **new_envp;
	int i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i  = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			ft_free_grid((void **)new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
