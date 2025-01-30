/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:20:51 by shachowd          #+#    #+#             */
/*   Updated: 2024/12/17 16:34:44 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(int fd, char c)
{
	if (write(fd, &c, 1) != 1)
	{
		return (-1);
	}
	return (1);
}

int	ft_print_percent(int fd)
{
	if (write(fd, "%", 1) != 1)
	{
		return (-1);
	}
	return (1);
}

char	*ft_strchr_pf(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char )c)
		return ((char *)s);
	return (0);
}
