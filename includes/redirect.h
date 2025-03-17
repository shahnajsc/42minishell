#ifndef REDIRECT_H
# define REDIRECT_H

typedef struct s_mshell t_mshell;
typedef enum e_redirect_type t_redirect_type;
typedef struct s_redirect t_redirect;

//...............FUNCTIONS................//
//..... ERROR HANDLE.....////
int		file_error(t_mshell *mshell, char *err_value, char *err_msg, int err_code);

//.......FILE FDs.......//
int		get_heredoc_fd(t_mshell *mshell, char *deli);
int		get_file_fd(t_mshell *mshell, char *path, t_redirect_type rd_type);

//........... REDIRECTs.............//
int		redirect_handle_cmd(t_mshell *mshell, t_redirect *rd_list, int *fd);
void	redirect_fd(int from_fd, int to_fd);

//.........HEREDOC.............//
void	heredoc_handle(t_mshell *mshell, char *deli, int hd_fd, char *hd_lines);


char	*read_line(int fd);
#endif

