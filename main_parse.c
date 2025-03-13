#include "minishell.h"

// void 	free_env(t_env *env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i].key != NULL)
// 	{
// 		free(env[i].key);
// 		free(env[i].value);
// 		i++;
// 	}
// 	free(env);
// }

// static int envp_size(char **envp)
// {
// 	int i;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	return (i);
// }

// static char *set_key_value(t_env *env, char *envp, char **sign)
// {
// 	int 		key_len;

// 	if (*sign)
// 	{
// 		key_len = *sign - envp;
// 		(*env).key = ft_strndup(envp, key_len);
// 		(*env).value = ft_strdup(*sign + 1);
// 		if (!(*env).key || !(*env).value)
// 			return (NULL);
// 	}
// 	else
// 	{
// 		(*env).key = ft_strdup(envp);
//     	(*env).value = NULL;
// 		if (!(*env).key)
// 			return (NULL);
// 	}
// 	return (envp);
// }

// int	env_duplicate(t_env **env, char **envp)
// {
// 	char	*sign;
// 	int		i;

// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		sign = ft_strchr(envp[i], '=');
// 		if (!set_key_value(&((*env)[i]), envp[i], &sign))
// 		{
// 			free_env(*env);
// 			return(-1);
// 		}
// 		i++;
// 	}
// 	(*env)[i].key = NULL;
// 	(*env)[i].value = NULL;
// 	return (0);
// }

// t_env	*init_env(char **envp)
// {
// 	t_env 		*env_list;
// 	int 		size;

// 	size = envp_size(envp);
// 	env_list = ft_calloc(sizeof(t_env), (size + 1));
// 	if (!env_list)
// 	{
// 		ft_putendl_fd("minishell: Allocation faild for env", STDERR_FILENO);
// 		return(NULL);
// 	}
// 	if (env_duplicate(&env_list, envp) != 0)
// 	{
// 		free(env_list);
// 		return (NULL);
// 	}
// 	//mshell_level(&env_list);
// 	return (env_list);
// }

// static int mshell_data_init(t_mshell *mshell, char **envp)
// {
// 	ft_memset(mshell, 0, sizeof(mshell));
// 	mshell->env = init_env(envp);
// 	if (!mshell->env)
// 		return (1);
// 	return (0);
// }



// int	main(int argc, char **argv, char **envp)
// {
// 	t_mshell mshell;

// 	if (argc != 1)
// 	{
// 		ft_putstr_fd("Error: Correct  argument: ./minishell\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	(void)argv;
// 	if (mshell_data_init(&mshell, envp))
// 		exit(EXIT_FAILURE);
// 	minishell(&mshell);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	data;
// 	int		pipe_status;

// 	pipe_status = 0;
// 	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
// 	{
// 		ft_putstr_fd("Correct  arguments: infile cmd1..cmd(n) outfile\n", 2);
// 		exit(1);
// 	}
// 	data_init(&data, argc, argv, envp);
// 	pipe_status = pipex(&data);
// 	clean_at_exit(&data);
// 	exit(pipe_status);
// }
