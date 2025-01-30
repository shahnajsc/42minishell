/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:35:12 by shachowd          #+#    #+#             */
/*   Updated: 2024/05/20 15:01:54 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_set(char const *str, char const c)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] == c)
			return (1);
		count++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		start;
	int		end;
	int		count;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && check_set(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while ((end > start) && check_set(set, s1[end - 1]))
		end--;
	ptr = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!ptr)
		return (NULL);
	count = 0;
	while (count < (end - start))
	{
		ptr[count] = s1[start + count];
		count++;
	}
	ptr[count] = '\0';
	return (ptr);
}
/* 
 - Allocates memory with malloc() for trimmed string.
- Trimmed string obtained from s1 by removing a specified 'set' of 
 	chararcters from begining and ending of s1.
- Returns NULL if memory allocation is failed. 
*/