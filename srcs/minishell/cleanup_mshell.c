#include "minishell.h"

void	cleanup_mshell(t_mshell *mshell)
{
	if (!mshell)
		return ;
	if (mshell->env)
		free_env(mshell->env);
	if (mshell->cmds)
		cleanup_on_loop(mshell);
}
