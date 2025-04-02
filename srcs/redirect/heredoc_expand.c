/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:55:00 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/01 21:50:10 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(t_mshell *mshell, char *joined_lines, int is_quote)
{
	char	*expanded_hd;

	if (!joined_lines || !mshell || *joined_lines == '\0')
	{
		if (joined_lines)
			free(joined_lines);
		return (NULL);
	}
	expanded_hd = NULL;
	if (is_quote)
	{
		expanded_hd = ft_strdup(joined_lines);
		if (joined_lines)
			free(joined_lines);
	}
	else
		expanded_hd = expand_text_token(mshell, joined_lines, 0);
	if (!expanded_hd)
	{
		if (joined_lines)
			free(joined_lines);
		return (NULL);
	}
	return (expanded_hd);
}
