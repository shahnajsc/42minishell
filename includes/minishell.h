/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:46:33 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/03 20:01:06 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// header files
# include "../libft/includes/libft.h"
# include "builtins.h"
# include "execution.h"
# include "parse.h"
# include "redirect.h"

// Library
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "minishell>> "

typedef struct s_mshell
{
	t_env	*env;
	int		count_cmds;
	t_cmd	*cmds;
	int		pipe_fd[2];
	int		prev_read_fd;
	pid_t	*p_id;
	int		exit_code;
	int		flag_path;
}	t_mshell;

extern volatile sig_atomic_t	g_heredoc;

int		minishell(t_mshell *mshell);
void	cleanup_mshell(t_mshell *mshell);

//........DEFAULT MINISHELL SIGNALS..........//
void	setup_signal_handlers();
void	ignore_parent_signals(void);

//........ HEREDOC SIGNALS..........//
void	setup_heredoc_signals(struct sigaction *sa_old);
int		heredoc_event_hook(void);

//........CHILD SIGNALS..........//
void	setup_child_signals(void);

#endif
