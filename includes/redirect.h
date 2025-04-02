/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:46:48 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/01 21:53:29 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

typedef struct s_mshell			t_mshell;
typedef enum e_redirect_type	t_redirect_type;
typedef struct s_redirect		t_redirect;
typedef struct s_cmd			t_cmd;
typedef struct s_token			t_token;

//...............FUNCTIONS................//
//..... ERROR HANDLE.....////
int								file_error(t_mshell *mshell, char *err_value,
									char *err_msg, int err_code);

//.......FILE FDs.......//
int								get_heredoc_fd(t_mshell *mshell,
									t_redirect *rd_list, int i);
int								get_file_fd(t_mshell *mshell, char *path,
									t_redirect_type rd_type);

//........... REDIRECTs.............//
int								redirect_handle_cmd(t_mshell *mshell,
									t_cmd *cmd, int len);
int								redirect_fd(int from_fd, int to_fd);

//.........HEREDOC.............//
int								heredoc_handle(t_mshell *mshell);
char							*expand_heredoc(t_mshell *mshell,
									char *hd_lines, int is_quote);

//...........UTILS..........//
int								mem_alloc_failed(char **joined_lines,
									char *line);
int								heredoc_join(char **joined_lines, char *line);

#endif
