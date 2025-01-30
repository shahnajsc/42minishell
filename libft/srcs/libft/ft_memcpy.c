/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:15:01 by shachowd          #+#    #+#             */
/*   Updated: 2024/05/20 10:56:28 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptrdst;
	char	*ptrsrc;

	ptrdst = (char *)dst;
	ptrsrc = (char *)src;
	if (!dst && !src)
	{
		return (0);
	}
	while (n--)
	{
		ptrdst[n] = ptrsrc[n];
	}
	return (dst);
}
/*
 - The memcpy() function copies n bytes from memory area s2 to 
 	memory area s1.
 - If s1 and s2 overlap, behavior is undefined. 
 - Applications in which s1 and s2 might overlap 
 		should use memmove(3) instead.
*/