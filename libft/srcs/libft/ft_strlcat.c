/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:15:31 by shachowd          #+#    #+#             */
/*   Updated: 2024/05/20 11:44:46 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstcount;
	size_t	srccount;

	if ((!dst || !src) && !dstsize)
		return (0);
	dstcount = 0;
	srccount = 0;
	while (dstcount < dstsize && dst[dstcount])
	{
		dstcount++;
	}
	while ((dstcount + srccount + 1) < dstsize && src[srccount])
	{
		dst[dstcount + srccount] = src[srccount];
		srccount++;
	}
	if (dstcount != dstsize)
	{
		dst[dstcount + srccount] = '\0';
	}
	return (dstcount + ft_strlen(src));
}
