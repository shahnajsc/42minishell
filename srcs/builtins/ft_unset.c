#include "minishell.h"

t_env 	*allocate_env_size(int env_size, int key_len)
{
	int 	new_env_size;
	t_env 	*new_env;

	new_env_size = env_size - key_len;
	new_env = ft_calloc(sizeof(t_env), new_env_size + 1); 
	if (!new_env)
		return (NULL);
	return (new_env);
}

int should_unset_var(t_env *env_var, char **keys, int keys_len)
{
    int index = 0;

    while (index < keys_len)
    {
        if (strcmp(env_var->key, keys[index]) == 0)
            return (1);  // Variable should be unset if there's a match
        index++;
    }
    return (0);  // No match found, so do not unset this variable
}

int count_keys(char **keys)
{
    int count;

	count = 0;
    while (keys[count] != NULL)
        count++;
    return (count);
}
int copy_variable(t_env *src_var, t_env *dest_var)
{
    dest_var->key = ft_strdup(src_var->key);
	if (src_var->value)
		dest_var->value =ft_strdup(src_var->value);
	else
		dest_var->value = NULL;
    if (!dest_var->key || (!dest_var->value && src_var->value))
        return (0); 
    return (1);
}


void ft_unset(t_mshell *mshell, char **keys, int i, int index)
{
    t_env *new_env;

    if (!mshell || !mshell->env || !keys)
        return;
    new_env = allocate_env_size(env_size(mshell->env), count_keys(keys));
    if (!new_env)
        return ;
    while (mshell->env[i].key != NULL)
    {
        if (!should_unset_var(&mshell->env[i], keys, count_keys(keys)))
        {
            if (!copy_variable(&mshell->env[i], &new_env[index]))
            {
                free_env(new_env);
                return ;
            }
            index++;
        }
        i++;
    }
    new_env[index].key = NULL;
    new_env[index].value = NULL;
    free_env(mshell->env);
    mshell->env = new_env;
}
