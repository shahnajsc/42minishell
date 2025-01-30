/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:14:07 by shachowd          #+#    #+#             */
/*   Updated: 2024/05/20 10:21:55 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			count;
	unsigned char	*ptr;

	count = 0;
	ptr = (unsigned char *)str;
	while (count < len)
	{
		ptr[count] = (unsigned char)c;
		count++;
	}
	return (str);
}
/*
 - It sets the first len bytes of the memory area pointed 
 		to by str to the specified value c
 - Return the pointer to the memory area.
- 'memset' will always overflow when null pointer passed
*/