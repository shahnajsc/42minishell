/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:17:00 by shachowd          #+#    #+#             */
/*   Updated: 2024/12/17 16:27:52 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(int fd, char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		if (write(fd, "(null)", 6) != 6)
		{
			return (-1);
		}
		return (6);
	}
	while (str[count])
	{
		if (write(fd, &str[count], 1) != 1)
		{
			return (-1);
		}
		count++;
	}
	return (count);
}
