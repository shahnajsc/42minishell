#ifndef EXECUTION_H
# define EXECUTION_H
typedef struct s_mshell t_mshell;
typedef enum e_redirect_type t_redirect_type;
typedef struct s_redirect t_redirect;

//...............EXECUTION................//
int		check_is_builtin(t_cmd *cmd);
void    execute_cmds(t_mshell *mshell);
int  	check_command_exec(t_mshell *mshell, int i, int *status);

//...............UTILS................//
void	parent_process(t_mshell *mshell);
int		wait_process(t_mshell *mshell, pid_t pid);
int		wait_all(t_mshell *mshell);
char	**convert_env(t_env *env, char ***copy_env);
char	*get_command_path(t_mshell *mshell, t_cmd *cmd);
void	child_process(t_mshell *mshell, int i, int *status);


//..... ERROR  && CLEANUP .....//
void 	close_fds(t_mshell *mshell);
int 	setup_pipe(t_mshell *mshell);
int 	allocate_pid(t_mshell *mshell);
int		create_child_process(t_mshell *mshell, pid_t p_id);

// //...............FUNCTIONS................//
// void	execute_cmds(t_mshell *mshell);
// char	*get_command_path(t_mshell *mshell, t_cmd *cmd);
// void	call_parent_process(t_mshell *mshell, int *pipe_fd, int i);
// void	call_child_process(t_mshell *mshell, int *pipe_fd, int i);
// int	builtins_in_parent(t_mshell *mshell, t_cmd *cmd);

// //...........UTILS............//
// int		check_is_builtin(t_cmd *cmd);
// char	**convert_env(t_env *env, char ***copy_env);
// int 	wait_processes(pid_t pid);

int	store_std_fd(t_mshell *mshell, t_cmd *cmd, int *status);
int	restore_std_fd(t_mshell *mshell, t_cmd *cmd, int *status);

#endif
