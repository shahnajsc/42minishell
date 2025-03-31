#include "minishell.h"

volatile sig_atomic_t	g_heredoc = 0;

static void	handle_heredoc_signals(int sig)
{
	(void)sig;
	g_heredoc = 1;
}

int	heredoc_event_hook(void)
{
	if (g_heredoc)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

void	setup_heredoc_signals(struct sigaction *sa_old)
{
	struct sigaction	new_sa;

	ft_memset(&new_sa, 0, sizeof(new_sa));
	new_sa.sa_handler = handle_heredoc_signals;
	new_sa.sa_flags = SA_RESTART;
	sigemptyset(&new_sa.sa_mask);
	if (sigaction(SIGINT, &new_sa, sa_old) == -1)
		return ;
}

void	ignore_parent_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return ;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return ;
}

void	setup_child_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return ;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return ;
}