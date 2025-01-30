/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:23:41 by shachowd          #+#    #+#             */
/*   Updated: 2024/05/16 16:09:09 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !del || !(*lst))
		return ;
	ft_lstclear(&(*lst)->next, del);
	(del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
/*
    - Deletes and frees the given node and every successor of that node.
    - Using the function ’del’ and 'free(3)'.
    - Finally, the pointer to the list must be set to NULL.
    - 'lst' The address of a pointer to a node.
    - 'del' The address of the function used to delete the content of the node.
	- 
*/