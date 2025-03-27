#include "minishell.h"

volatile sig_atomic_t g_heredoc = 0;

void 	reset_prompt(int sigint)
{
	(void)sigint;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void 	reset_sigint()
{
	printf("minishell default setting ..\n");
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = reset_prompt;
	sigemptyset(&sa.sa_mask); 
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return ;
}
void  ignore_sigquit()
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask); 
	if (sigaction(SIGQUIT, &sa, NULL) == -1 )
		return ;
}

void handle_heredoc_signals(int sig)
{
	(void)sig;
	g_heredoc = 1;
}

void 	setup_heredoc_signals(struct sigaction *sa_old)
{
	printf("heredoc catches the signal ..\n");
	struct sigaction new_sa;

	ft_memset(&new_sa, 0, sizeof(new_sa));
    new_sa.sa_handler = handle_heredoc_signals;
    new_sa.sa_flags = SA_RESTART;  // Important for proper readline behavior
    sigemptyset(&new_sa.sa_mask);
    sigaction(SIGINT, &new_sa, sa_old);


	// sa.sa_handler = SIG_IGN;
    // sigaction(SIGQUIT, &sa, NULL);
}

void    setup_terminal(void)
{
    int             fd;
    struct termios terminal;

    fd = STDIN_FILENO;
    if (tcgetattr(fd, &terminal) == -1)
        return ;
    terminal.c_lflag &= ~ECHOCTL;
    if (tcsetattr(fd, TCSANOW, &terminal) == -1)
        return ;
}
void    setup_signal_handlers(void)
{
    setup_terminal();
    ignore_sigquit();
    reset_sigint();
}
