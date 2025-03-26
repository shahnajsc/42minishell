#include "minishell.h"

char	*expand_heredoc(t_mshell *mshell, char *hd_lines, int is_quote)
{
	char	*expanded_hd;

	if (!hd_lines)
		return (NULL);
	expanded_hd = NULL;
	if (is_quote)
		expanded_hd = ft_strdup(hd_lines);
	else
		expanded_hd = expand_text_token(mshell, hd_lines);
	if (hd_lines)
		free(hd_lines);
	if (!expanded_hd)
		return (NULL);
	return(expanded_hd);
}
