#include "minishell.h"

static void	reset_prompt(int sigint)
{
	(void)sigint;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	reset_sigint(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = reset_prompt;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return ;
}

static void	ignore_sigquit(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return ;
}

static void	setup_terminal(void)
{
	int				fd;
	struct termios	terminal;

	fd = STDIN_FILENO;
	if (tcgetattr(fd, &terminal) == -1)
		return ;
	terminal.c_lflag &= ~ECHOCTL;
	if (tcsetattr(fd, TCSANOW, &terminal) == -1)
		return ;
}

void	setup_signal_handlers(void)
{
	setup_terminal();
	ignore_sigquit();
	reset_sigint();
}