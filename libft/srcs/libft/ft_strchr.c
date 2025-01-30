/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:12:03 by shachowd          #+#    #+#             */
/*   Updated: 2024/09/26 16:41:32 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char )c)
		return ((char *)s);
	return (0);
}
/*
	-It locates the FIRST occurence of 'c' in the string.
	- 'c' converted to a char.
	- '\0' NULL terminator is also considered as character of string 's'
		and locates.
	- Returns pointer to the located character or NULL if no occurence.
*/
