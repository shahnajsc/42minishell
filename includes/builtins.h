#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char	*key;
	char	*value;

}			t_env;

// typedef struct s_built_state {
// 	char 		*pwd;
// 	char 		*old_pwd;
// 	int 		pwd_exec;
// 	int 		oldpwd_exec;
// } t_built_state;

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
}			t_cd_error;

//........BUILTINS..........//
int			builtins_exec(t_mshell *mshell);
int			ft_pwd(t_mshell *mshell);
int			ft_cd(t_mshell *mshell, char **args);
int			ft_env(t_mshell *mshell, char **args);
int			ft_exit(t_mshell *mshell, char **args);
int			ft_echo(t_mshell *mshell, char **args);
int			ft_export(t_mshell *mshell, char **args);
int			ft_unset(t_mshell *mshell, char **keys, int i, int index);

//........UTILS..........//
t_env		*init_env(char **envp);
int			env_size(t_env *env);
char		*ft_strndup(char *src, size_t n);
t_env		*get_env_var(t_env *env, char *key);
void		process_without_sign(t_env **env, char *arg);
void		add_env_var(t_env **old_env, char *key, char *value);
void		process_with_sign(t_env **env, char *arg, char *sign);
int			update_env_state(t_mshell *mshell, char *current_pwd);
void		update_cd(t_env **env, const char *key, const char *set_path);

//........VALIDATION.........//
int			is_invalid_digit(char *arg);
int			is_invalid_identifier(char *identifier);

//..... ERROR  && CLEANUP .....//
void		free_env(t_env *env);
int			exit_mshell(t_mshell *mshell);
int			cd_error(char **args, t_cd_error err);
int			mshell_lvl_error(t_env **env, char *new_lvl);
int			builtins_error(char *arg, char *err_msg, char *free_str);

//........SIGNALS..........//
void		setup_signal_handlers(void);

#endif
