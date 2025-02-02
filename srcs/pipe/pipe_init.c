#include "./minishell.h"


static int	**pipe_fds(int argc, int is_here_doc)
{
	int	**fds;
	int	i;

	i = -1;
	fds = (int **)malloc((argc - 3 - is_here_doc + 1) * sizeof(int *));
	if (!fds)
		return (NULL);
	while (fds && ++i < (argc - 3 - is_here_doc))
	{
		fds[i] = (int *)malloc(2 * sizeof(int));
		if (!fds[i])
		{
			free_grid((void **)fds);
			return (NULL);
		}
	}
	fds[i] = NULL;
	return (fds);
}

static void	data_init(t_pipex *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		data->here_doc = 1;
	else
		data->here_doc = 0;
	data->fd = pipe_fds(argc, data->here_doc);
	if (!data->fd)
		error_return(data, "malloc()", "", 1);
	data->envp_paths = NULL;
	data->sp_cmd = NULL;
}


