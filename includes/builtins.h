#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env {

	char		*key;
	char		*value;

} t_env;

typedef struct s_built_state {
	char 		*pwd;
	char 		*old_pwd;
	int 		pwd_exec;
	int 		oldpwd_exec;
} t_built_state;

typedef enum s_cd_error
{
	SUCSSES,
	FAILURE,
	NO_FILE,
	NOT_DIR,
	NO_PERM,
	HOME_UNSET,
	MANY_ARGS,
	GETCWD,
} t_cd_error;


int				ft_env(t_mshell *mshell, char **args);
int				ft_pwd(t_mshell *mshell);
int 			builtins_error(char *arg, char *err_msg, char *free_str);
int 			ft_cd(t_mshell *mshell, char **args);
char 			*ft_strndup(char *src, size_t n);
void			set_env_variable(t_mshell *mshell, char **args, int *err_code);
void 			free_env(t_env *env);
int			ft_echo(t_mshell *mshell, char **args);
int 			ft_unset(t_mshell *mshell, char **keys, int i, int index);
t_env 			*get_env_var(t_env *env, char *key);
void   			add_env_var(t_env **env, char *key, char *value);
int				update_env_state(t_mshell *mshell, char *current_pwd);
int 			cd_error(char **args, t_cd_error err);
int 			builtins_execv(t_mshell *mshell);
t_built_state 	*init_built_state();
int 			ft_export(t_mshell *mshell, char **args);
t_env			*init_env(char **envp);
int 			is_invalid_identifier(char *identifier);
int				mshell_lvl_error(t_env **env, char *new_lvl);
int 			env_size(t_env *env);
t_env  			*allocate_new_env(t_env *old_env);
int  			ft_exit(t_mshell *mshell, char **args);
int 			is_invalid_digit(char *arg);
void			update_cd_env(t_env **env, const char *key, const char *set_path);
void  			setup_signal_handlers();
int 			exit_mshell(t_mshell *mshell);
#endif

