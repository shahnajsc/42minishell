/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:31:36 by shachowd          #+#    #+#             */
/*   Updated: 2024/05/20 12:48:00 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*str;
	unsigned char	ch;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	count = 0;
	while (count < n)
	{
		if (*str == ch)
		{
			return (str);
		}
		str++;
		count++;
	}
	return (NULL);
}

/*
 - The ft_memchr() function locates the first occurrence 
 		of c (converted to an unsigned char) in string s
 - Returns a pointer to the byte located, or NULL
 - if no such byte exists within n bytes.
*/