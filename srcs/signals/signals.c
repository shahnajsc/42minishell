#include "minishell.h"

void 	reset_prompt()
{
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void 	reset_sigint()
{
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
void  setup_signal_handlers()
{
	ignore_sigquit();

	
}
