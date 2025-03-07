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
	NO_FILE,
	NOT_DIR,
	NO_PERM,
	HOME_UNSET,
	CMN_ERR,
	TOO_MANY_ARGS,
} t_cd_error;


int				ft_env(t_mshell *mshell, char **args);
int				ft_pwd(void);
int 			builtins_error(char *arg, char *err_msg, char *free_str);
int 			ft_cd(t_mshell *mshell, char **args);
char 			*ft_strndup(char *src, size_t n);
void			set_env_variable(t_mshell *mshell, char **args, int *err_code);
void 			free_env(t_env *env);
void			ft_echo(t_mshell *mshell, char **args);
void			ft_unset(t_env **env, char *key);
t_env 			*get_env_var(t_env *env, char *key);
void   			add_env_var(t_env **env, char *key, char *value);
int				update_env_state(t_mshell *mshell, char **oldpwd, char **pwd);
int 			cd_error(char **args, t_cd_error err);
int 			builtins_execv(t_mshell *mshell, char *input_str);
t_built_state 	*init_built_state();
int 			ft_export(t_mshell *mshell, char **args);
t_env			*init_env(char **envp);
int 			is_invalid_identifier(char *identifier);
int				mshell_lvl_error(t_env **env, char *new_lvl);
int 			env_size(t_env *env);
t_env  			*allocate_new_env(t_env *old_env);
int  			ft_exit(t_mshell *mshell, char **args);
int 			is_invalid_digit(char *arg);
#endif