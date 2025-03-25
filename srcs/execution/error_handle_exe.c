#include "minishell.h"

int 	allocate_pid(t_mshell *mshell)
{
	mshell->p_id = ft_calloc(mshell->count_cmds + 1, sizeof(pid_t));
	if (!mshell->p_id)
	{
		ft_putstr_fd("minishell: pid alloc failed\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

void 	close_fds(t_mshell *mshell)
{
    if (mshell->pipe_fd[0] != -1) 
	{
        close(mshell->pipe_fd[0]);
        mshell->pipe_fd[0] = -1;
    }
    if (mshell->pipe_fd[1] != -1) 
	{
        close(mshell->pipe_fd[1]);
        mshell->pipe_fd[1] = -1;
    }
	if (mshell->prev_read_fd != STDIN_FILENO)
    {    
		close(mshell->prev_read_fd);
		mshell->prev_read_fd = STDIN_FILENO;
	}
}

int		create_child_process(t_mshell *mshell, pid_t p_id)
{
	if (p_id == -1)
	{
		perror("minishell: fork");
		close_fds(mshell);
		free(mshell->p_id);
       	return (-1);
	}
	return (0);
}

int 	setup_pipe(t_mshell *mshell)
{
	if (pipe(mshell->pipe_fd) == -1)
	{
		perror("minishell: pipe");
		close_fds(mshell);
		free(mshell->p_id);
		return (-1);
	}
	return (0);
}
