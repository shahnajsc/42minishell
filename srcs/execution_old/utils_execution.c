// #include "minishell.h"

// char **convert_env(t_env *env, char ***copy_env)
// {
//     int i;
//     int len;

//     *copy_env = ft_calloc(env_size(env) + 1, sizeof(char *));
//     if (!(*copy_env))
//         return (NULL);
//     i = 0;
//     while (env[i].key != NULL)
//     {
//         len = ft_strlen(env[i].key) + ft_strlen(env[i].value) + 2;  // +2 for '=' and '\0'
//         (*copy_env)[i] = ft_calloc(len, sizeof(char));
//         if (!(*copy_env)[i])
//         {
//             ft_free_grid((void **)(*copy_env));
//             return (NULL);
//         }
//         ft_strlcpy((*copy_env)[i], env[i].key, ft_strlen(env[i].key) + 1);
//         ft_strlcat((*copy_env)[i], "=", len);
//         ft_strlcat((*copy_env)[i], env[i].value, len);
//         i++;
//     }
// 	(*copy_env)[i] = NULL;
//     return (*copy_env);
// }

// int 	wait_processes(pid_t pid)
// {
// 	int	wstatus;

// 	waitpid(pid, &wstatus, 0);
// 	if (WIFEXITED(wstatus))
// 		return (WEXITSTATUS(wstatus));
// 	return (1);
// }
